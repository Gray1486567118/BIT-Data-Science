import json
from sklearn.metrics import accuracy_score, f1_score, roc_auc_score
import numpy as np

# 读取 JSON 文件
def read_json(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
    return data

# 定义评估指标计算
def compute_metrics(eval_pred):
    disease_logits, syndrome_logits = eval_pred.predictions # 获取模型的两个输出
    disease_labels, syndrome_labels = eval_pred.label_ids # 获取真实标签

    # --- Disease 任务评估 ---
    disease_predictions = np.argmax(disease_logits, axis=1)
    disease_accuracy = accuracy_score(disease_labels, disease_predictions)
    disease_f1_weighted = f1_score(disease_labels, disease_predictions, average='weighted')

    # --- Syndrome 任务评估 (多标签) ---
    # 对 syndrome_logits 应用 Sigmoid (BCEWithLogitsLoss 内部做了 Sigmoid)
    syndrome_probabilities = 1 / (1 + np.exp(-syndrome_logits)) 
    # 将概率转换为二进制预测 (例如，阈值0.5)
    syndrome_predictions = (syndrome_probabilities > 0.5).astype(int) 
    
    syndrome_f1_micro = f1_score(syndrome_labels, syndrome_predictions, average='micro')
    syndrome_f1_macro = f1_score(syndrome_labels, syndrome_predictions, average='macro')
    

    return {
        "disease_accuracy": disease_accuracy,
        "disease_f1_weighted": disease_f1_weighted,
        "syndrome_f1_micro": syndrome_f1_micro,
        "syndrome_f1_macro": syndrome_f1_macro,
    }