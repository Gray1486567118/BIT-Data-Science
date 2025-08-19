import torch
import json
import numpy as np
from torch.utils.data import DataLoader
from sklearn.metrics import accuracy_score
from model_nn import MultiTaskNN
from dataset_nn import TCMNumericDataset, read_json

# --- 1. 定义文件路径和参数 ---
MODEL_LOAD_PATH = "./numeric_model_output/best_model.pth"
TEST_INPUT_PATH = "../data/test_input.json"
TEST_OUTPUT_PATH = "../data/test_output.json"
PREDICTIONS_SAVE_PATH = "./numeric_predictions.json"

NUM_DISEASE_LABELS = 4
NUM_SYNDROME_LABELS = 10

HIDDEN_DIM = 128 
DROPOUT_PROB = 0.3


# --- 2. 设置设备 ---
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")


# --- 3. 加载测试数据 ---
print(f"Loading test data from {TEST_INPUT_PATH}...")
test_data = read_json(TEST_INPUT_PATH)
test_dataset = TCMNumericDataset(test_data, NUM_DISEASE_LABELS, NUM_SYNDROME_LABELS)
test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False)

# 自定义 collate_fn
def predict_collate_fn(batch):
    features = torch.stack([item["features"] for item in batch])
    ids = [item["ID"] for item in batch]
    return {
        "features": features,
        "ID": ids
    }

test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False, collate_fn=predict_collate_fn) 

INPUT_DIM = test_dataset.input_dim


# --- 4. 加载模型 ---
print(f"Loading model from {MODEL_LOAD_PATH}...")
model = MultiTaskNN(INPUT_DIM, NUM_DISEASE_LABELS, NUM_SYNDROME_LABELS, HIDDEN_DIM, DROPOUT_PROB).to(device)
model.load_state_dict(torch.load(MODEL_LOAD_PATH, map_location=device))
model.eval()


# --- 5. 进行预测 ---
print("Starting prediction...")
all_ids = []
all_disease_preds = []
all_syndrome_preds_multi_hot = []
all_syndrome_preds_list = []

with torch.no_grad():
    for batch_idx, batch in enumerate(test_loader):
        features = batch["features"].to(device)
        ids = batch["ID"]

        outputs = model(features)
        disease_logits = outputs["disease_logits"]
        syndrome_logits = outputs["syndrome_logits"]

        # 预测disease
        disease_predictions = torch.argmax(disease_logits, dim=-1).cpu().numpy()
        all_disease_preds.extend(disease_predictions)

        # 预测syndrome
        syndrome_probabilities = torch.sigmoid(syndrome_logits)
        syndrome_probabilities_np = syndrome_probabilities.cpu().numpy()

        syndrome_predictions_multi_hot_batch = []
        syndrome_predictions_list_batch = []

        for i in range(syndrome_probabilities_np.shape[0]): # 遍历batch中每个样本
            sample_probs = syndrome_probabilities_np[i, :]

            # 选择概率大于0.5的标签
            positive_indices = np.where(sample_probs > 0.5)[0]
            
            if len(positive_indices) > 0:
                # 如果有概率大于0.5的，就使用这些标签
                predicted_indices_for_sample = positive_indices
            else:
                # 如果所有概率都小于0.5，则选择概率最大的那个标签
                max_prob_index = np.argmax(sample_probs)
                predicted_indices_for_sample = np.array([max_prob_index])
            
            # 转换为 Multi-Hot
            multi_hot_prediction = np.zeros(NUM_SYNDROME_LABELS, dtype=int)
            multi_hot_prediction[predicted_indices_for_sample] = 1
            syndrome_predictions_multi_hot_batch.append(multi_hot_prediction)
            
            # 转换为列表
            syndrome_predictions_list_batch.append(predicted_indices_for_sample.tolist())

        all_syndrome_preds_multi_hot.extend(syndrome_predictions_multi_hot_batch)
        all_syndrome_preds_list.extend(syndrome_predictions_list_batch)
        
        all_ids.extend(ids)


# --- 6. 保存预测结果 ---
predictions_output = []
for i in range(len(all_ids)):
    predictions_output.append({
        "ID": all_ids[i],
        "predicted_disease": int(all_disease_preds[i]),
        "predicted_syndrome": all_syndrome_preds_list[i]
    })

print(f"Saving predictions to {PREDICTIONS_SAVE_PATH}...")
with open(PREDICTIONS_SAVE_PATH, "w", encoding="utf-8") as f:
    json.dump(predictions_output, f, ensure_ascii=False, indent=2)
print("Prediction complete.")


# --- 7. 加载真实标签并进行评估 ---
print(f"Loading ground truth from {TEST_OUTPUT_PATH}...")
with open(TEST_OUTPUT_PATH, "r", encoding="utf-8") as f:
    gt_data_map = {item["ID"]: item for item in json.load(f)}

y_true_disease = []
y_pred_disease = []
y_true_syndrome = [] 
y_pred_syndrome = []

for i in range(len(all_ids)):
    id_ = all_ids[i]
    if id_ in gt_data_map:
        gt_item = gt_data_map[id_]
        
        # 处理 disease 的单标签预测
        y_true_disease.append(gt_item["disease"])
        y_pred_disease.append(all_disease_preds[i])

        # 处理 syndrome 的多标签预测
        true_syndrome_multi_hot = np.zeros(NUM_SYNDROME_LABELS, dtype=int)
        if "syndrome" in gt_item and gt_item["syndrome"] is not None:
            for label_idx in gt_item["syndrome"]:
                if 0 <= label_idx < NUM_SYNDROME_LABELS:
                    true_syndrome_multi_hot[label_idx] = 1
        y_true_syndrome.append(true_syndrome_multi_hot)
        
        y_pred_syndrome.append(all_syndrome_preds_multi_hot[i])
    else:
        print(f"Warning: ID {id_} from predictions not found in ground truth. Skipping this sample for evaluation.")

if not y_true_disease:
    print("Error: No matching IDs found between predictions and ground truth for evaluation.")
else:
    y_true_disease = np.array(y_true_disease)
    y_pred_disease = np.array(y_pred_disease)
    y_true_syndrome = np.array(y_true_syndrome)
    y_pred_syndrome = np.array(y_pred_syndrome)


    # --- 8. 输出评估结果 ---
    print("\n--- Final Evaluation Results ---")

    print("\n--- Disease Classification Metrics ---")
    disease_accuracy = accuracy_score(y_true_disease, y_pred_disease)
    print(f"Disease Accuracy: {disease_accuracy:.4f}")

    print("\n--- Syndrome Metrics ---")
    
    # 自定义Syndrome正确率
    syndrome_recall_custom = []
    for i in range(len(y_true_syndrome)):
        true_set = set(np.where(y_true_syndrome[i] == 1)[0])
        pred_set = set(np.where(y_pred_syndrome[i] == 1)[0])
        
        if len(true_set) > 0:
            intersection_size = len(true_set.intersection(pred_set))
            recall_for_sample = intersection_size / len(true_set)
            syndrome_recall_custom.append(recall_for_sample)
        else:
            if len(pred_set) == 0:
                syndrome_recall_custom.append(1.0)
            else:
                syndrome_recall_custom.append(0.0)
                
    if syndrome_recall_custom:
        avg_syndrome_recall_custom = np.mean(syndrome_recall_custom)
        print(f"Syndrome Accuracy: {avg_syndrome_recall_custom:.4f}")
