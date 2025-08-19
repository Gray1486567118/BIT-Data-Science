# eval.py

import json
from sklearn.metrics import accuracy_score
import numpy as np

# --- 1. 读取预测结果和标准答案 ---
with open("./data/test_output.json", "r", encoding="utf-8") as f:
    gt_data = {item["ID"]: item["disease"] for item in json.load(f)}

with open("predictions.json", "r", encoding="utf-8") as f:
    pred_data = json.load(f)

# --- 2. 匹配预测和真实标签 ---
y_true_disease = []
y_pred_disease = []
y_true_syndrome = [] 
y_pred_syndrome = []

for item in pred_data:
    id_ = item["ID"]
    pred_disease = item["predicted_disease"]
    true_disease = gt_data.get(id_)
    
    y_pred_disease.append(pred_disease)
    y_true_disease.append(true_disease)

# 3. 输出评估结果
print("Accuracy:", accuracy_score(y_true_disease, y_pred_disease))

