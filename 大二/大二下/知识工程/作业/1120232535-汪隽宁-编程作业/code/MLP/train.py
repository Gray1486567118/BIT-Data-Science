import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
import yaml
from sklearn.metrics import accuracy_score, f1_score
import numpy as np
import os
import datetime

from model_nn import MultiTaskNN
from dataset_nn import TCMNumericDataset, read_json


# --- 0. 读取配置文件 ---
with open("./mlp/config_nn.yaml", "r", encoding="utf-8") as f:
    cfg = yaml.safe_load(f)

# --- 1. 设置设备 ---
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# --- 2. 参数设置 ---
NUM_DISEASE_LABELS = cfg.get('num_disease_labels', 4)
NUM_SYNDROME_LABELS = cfg.get('num_syndrome_labels', 10)
INPUT_DIM = cfg.get('input_dim', 63)
HIDDEN_DIM = cfg.get('hidden_dim', 128)
DROPOUT_PROB = cfg.get('dropout_prob', 0.3)
EPOCHS = cfg.get('epochs', 50)
BATCH_SIZE = cfg.get('batch_size', 32)
LEARNING_RATE = cfg.get('learning_rate', 1e-3)
SAVE_PATH = cfg.get('save_path', "./numeric_model_output")
LOG_INTERVAL = cfg.get('log_interval', 10)

os.makedirs(SAVE_PATH, exist_ok=True)


# --- 3. 准备数据集和数据加载器 ---
print("Loading data...")
train_data = read_json(cfg['train_path'])
val_data = read_json(cfg['val_path'])

train_dataset = TCMNumericDataset(train_data, NUM_DISEASE_LABELS, NUM_SYNDROME_LABELS)
val_dataset = TCMNumericDataset(val_data, NUM_DISEASE_LABELS, NUM_SYNDROME_LABELS)

# 确保input_dim在TCMNumericDataset初始化后正确设置
if train_dataset.input_dim != INPUT_DIM:
    print(f"Warning: Configured INPUT_DIM ({INPUT_DIM}) does not match detected input dimension ({train_dataset.input_dim}). Using detected dimension.")
    INPUT_DIM = train_dataset.input_dim

train_loader = DataLoader(train_dataset, batch_size=BATCH_SIZE, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=BATCH_SIZE, shuffle=False)
print("Data loaded.")


# --- 4. 初始化模型、损失函数和优化器 ---
model = MultiTaskNN(INPUT_DIM, NUM_DISEASE_LABELS, NUM_SYNDROME_LABELS, HIDDEN_DIM, DROPOUT_PROB).to(device)
optimizer = optim.Adam(model.parameters(), lr=LEARNING_RATE)


# --- 5. 定义评估函数 ---
def evaluate_model(model, data_loader, device):
    model.eval()
    
    all_disease_preds = []
    all_disease_labels = []
    all_syndrome_preds_multi_hot = []
    all_syndrome_labels_multi_hot = []
    
    with torch.no_grad():
        for batch_idx, batch in enumerate(data_loader):
            features = batch["features"].to(device)
            disease_labels = batch["disease_labels"].to(device)
            syndrome_labels = batch["syndrome_labels"].to(device)

            outputs = model(features)
            disease_logits = outputs["disease_logits"]
            syndrome_logits = outputs["syndrome_logits"]

            # 预测disease
            disease_predictions = torch.argmax(disease_logits, dim=-1).cpu().numpy()
            all_disease_preds.extend(disease_predictions)
            all_disease_labels.extend(disease_labels.cpu().numpy())

            # 预测syndrome
            syndrome_probabilities = torch.sigmoid(syndrome_logits)
            syndrome_predictions_multi_hot = (syndrome_probabilities > 0.5).int().cpu().numpy()
            all_syndrome_preds_multi_hot.extend(syndrome_predictions_multi_hot)
            all_syndrome_labels_multi_hot.extend(syndrome_labels.int().cpu().numpy())

    all_disease_preds = np.array(all_disease_preds)
    all_disease_labels = np.array(all_disease_labels)
    all_syndrome_preds_multi_hot = np.array(all_syndrome_preds_multi_hot)
    all_syndrome_labels_multi_hot = np.array(all_syndrome_labels_multi_hot)

    # --- Disease Metrics ---
    disease_accuracy = accuracy_score(all_disease_labels, all_disease_preds)
    disease_f1_weighted = f1_score(all_disease_labels, all_disease_preds, average='weighted', zero_division=0)

    # --- Syndrome Metrics ---
    syndrome_f1_micro = f1_score(all_syndrome_labels_multi_hot, all_syndrome_preds_multi_hot, average='micro', zero_division=0)
    syndrome_f1_macro = f1_score(all_syndrome_labels_multi_hot, all_syndrome_preds_multi_hot, average='macro', zero_division=0)
    
    # 自定义正确率
    syndrome_recall_custom = []
    for i in range(len(all_syndrome_labels_multi_hot)):
        true_set = set(np.where(all_syndrome_labels_multi_hot[i] == 1)[0])
        pred_set = set(np.where(all_syndrome_preds_multi_hot[i] == 1)[0])
        
        if len(true_set) > 0:
            intersection_size = len(true_set.intersection(pred_set))
            recall_for_sample = intersection_size / len(true_set)
            syndrome_recall_custom.append(recall_for_sample)
        else:
            if len(pred_set) == 0:
                syndrome_recall_custom.append(1.0) # True empty, Pred empty -> perfect match
            else:
                syndrome_recall_custom.append(0.0) # True empty, Pred not empty -> imperfect match
    
    avg_syndrome_recall_custom = np.mean(syndrome_recall_custom) if syndrome_recall_custom else 0.0

    return {
        "disease_accuracy": disease_accuracy,
        "disease_f1_weighted": disease_f1_weighted,
        "syndrome_f1_micro": syndrome_f1_micro,
        "syndrome_f1_macro": syndrome_f1_macro,
        "syndrome_custom_recall": avg_syndrome_recall_custom
    }

# --- 6. 训练循环 ---
print("Starting training...")
best_val_f1_combined = -1

for epoch in range(EPOCHS):
    model.train()
    total_loss = 0
    start_time = datetime.datetime.now()

    for batch_idx, batch in enumerate(train_loader):
        features = batch["features"].to(device)
        disease_labels = batch["disease_labels"].to(device)
        syndrome_labels = batch["syndrome_labels"].to(device)

        optimizer.zero_grad()
        outputs = model(features, disease_labels, syndrome_labels)
        loss = outputs["loss"]
        loss.backward()
        optimizer.step()

        total_loss += loss.item()

        if (batch_idx + 1) % LOG_INTERVAL == 0:
            print(f"Epoch [{epoch+1}/{EPOCHS}], Batch [{batch_idx+1}/{len(train_loader)}], Loss: {loss.item():.4f}")

    avg_train_loss = total_loss / len(train_loader)
    end_time = datetime.datetime.now()
    time_taken = (end_time - start_time).total_seconds()

    print(f"\n--- Epoch {epoch+1} Summary ---")
    print(f"Average Training Loss: {avg_train_loss:.4f}")
    print(f"Time taken for epoch: {time_taken:.2f} seconds")

    # 验证阶段
    val_metrics = evaluate_model(model, val_loader, device)
    print(f"Validation Metrics:")
    print(f"  Disease Accuracy: {val_metrics['disease_accuracy']:.4f}")
    print(f"  Disease F1 (Weighted): {val_metrics['disease_f1_weighted']:.4f}")
    print(f"  Syndrome F1 (Micro): {val_metrics['syndrome_f1_micro']:.4f}")
    print(f"  Syndrome F1 (Macro): {val_metrics['syndrome_f1_macro']:.4f}")
    print(f"  Syndrome Custom Recall: {val_metrics['syndrome_custom_recall']:.4f}")

    # 保存最佳模型，使用 Disease F1 和 Syndrome Micro F1 的平均值作为保存标准
    current_val_f1_combined = (val_metrics['disease_f1_weighted'] + val_metrics['syndrome_f1_micro']) / 2
    if current_val_f1_combined > best_val_f1_combined:
        best_val_f1_combined = current_val_f1_combined
        model_save_path = os.path.join(SAVE_PATH, "best_model.pth")
        torch.save(model.state_dict(), model_save_path)
        print(f"Saved best model to {model_save_path} with combined F1: {best_val_f1_combined:.4f}")

print("\nTraining complete!")