import torch
import json
from transformers import AutoTokenizer, AutoConfig
from dataset import TCMDataset
from model import QwenForTCM

# --- 1. 定义模型和分词器保存路径 ---
# 这个路径应该与 train.py 中 cfg['save_path'] 的值一致
MODEL_PATH = "./save_model" # 替换为你的模型实际保存路径

# --- 2. 加载分词器和模型 ---
print(f"Loading tokenizer from {MODEL_PATH}...")
tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH)
# 确保 pad_token 再次设置为 eos_token，与训练时保持一致
tokenizer.pad_token = tokenizer.eos_token 

print(f"Loading model from {MODEL_PATH}...")
config = AutoConfig.from_pretrained(MODEL_PATH)
config.num_labels = 4 
model = QwenForTCM.from_pretrained(MODEL_PATH, config=config)
model.eval() # 设置模型为评估模式

model.to("cuda")
print("Model moved to GPU.")

print("\n--- Model loaded. Checking model parameters: ---")


# --- 3. 准备测试数据 ---
test_input_path = "./data/test_input.json" 
print(f"Loading test data from {test_input_path}...")
with open(test_input_path, "r", encoding="utf-8") as f:
    test_data = json.load(f)

test_dataset = TCMDataset(test_data, tokenizer, mode="test")


# --- 4. 进行预测 ---
predictions = []
with torch.no_grad(): 
    for i, item in enumerate(test_dataset):
        input_ids = item["input_ids"].unsqueeze(0) # 添加 batch 维度
        attention_mask = item["attention_mask"].unsqueeze(0) # 添加 batch 维度

        if torch.cuda.is_available():
            input_ids = input_ids.to("cuda")
            attention_mask = attention_mask.to("cuda")

        outputs = model(input_ids=input_ids, attention_mask=attention_mask)
        
        # 获取预测logits
        disease_logits = outputs["disease_logits"]
        syndrome_logits = outputs["syndrome_logits"] # 未经 Sigmoid 的原始输出

        # 疾病预测结果
        predicted_disease_id = torch.argmax(disease_logits, dim=-1).item()

        # 症状预测结果
        syndrome_probabilities = torch.sigmoid(syndrome_logits)
        predicted_syndrome_ids = (syndrome_probabilities > 0.5).squeeze(0).cpu().numpy().tolist()
    
        if predicted_syndrome_ids == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]:
            max_prob_id = torch.argmax(syndrome_probabilities, dim=1).item()
            predicted_syndrome_ids[max_prob_id] = 1

        actual_predicted_syndrome_labels = [idx for idx, val in enumerate(predicted_syndrome_ids) if val == 1]


        # 获取原始数据的ID
        original_id = test_data[i]["ID"]

        predictions.append({
            "ID": original_id,
            "predicted_disease": predicted_disease_id,
            "predicted_syndrome": actual_predicted_syndrome_labels
        })


# --- 5. 保存预测结果 ---
output_prediction_path = "predictions.json"
print(f"Saving predictions to {output_prediction_path}...")
with open(output_prediction_path, "w", encoding="utf-8") as f:
    json.dump(predictions, f, ensure_ascii=False, indent=2)

print("Prediction complete and results saved.")