import json
import torch
import yaml
from torch.utils.data import DataLoader
from transformers import BertTokenizerFast, AutoTokenizer, AutoModelForCausalLM
from model import BertForTCM
from dataset import TCMDataset
from sklearn.metrics import accuracy_score
from tqdm import tqdm

import os
os.environ['CUDA_LAUNCH_BLOCKING'] = '1'

# ------------------------
# Step 1: 加载配置
# ------------------------
with open("config.yaml", "r", encoding="utf-8") as f:
    cfg = yaml.safe_load(f)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# ------------------------
# Step 2: 加载 tokenizer & dataset
# ------------------------
tokenizer = BertTokenizerFast.from_pretrained(cfg['model_name'])
test_dataset = TCMDataset(
    path="./data/test_input.json",
    tokenizer_name=cfg['model_name'],
    max_length=cfg['max_length'],
    mode="test"
)
test_loader = DataLoader(test_dataset, batch_size=cfg['eval_batch_size'], shuffle=False)

# ------------------------
# Step 3: 加载模型
# ------------------------
model = BertForTCM.from_pretrained(cfg['output_dir'])
model.to(device)
model.eval()

# ------------------------
# Step 4: 加载标准答案
# ------------------------
gold_data = json.load(open("./data/test_output.json", "r", encoding="utf-8"))
gold_map = {item['ID']: item for item in gold_data}

# ------------------------
# Step 5: 开始评估
# ------------------------
all_pred_syn = []
all_true_syn = []
all_pred_dis = []
all_true_dis = []

for batch in tqdm(test_loader, desc="Evaluating"):
    batch = {k: v.to(device) if isinstance(v, torch.Tensor) else v for k, v in batch.items()}
    with torch.no_grad():
        outputs = model(
            input_ids=batch['input_ids'],
            attention_mask=batch['attention_mask'],
            struct_feat=batch['struct_feat']
        )

    probs_syn = torch.sigmoid(outputs['logits_syndrome'])  # [B, 10]
    probs_dis = outputs['logits_disease']                  # [B, 4]

    for i in range(len(batch['ID'])):
        ID = batch['ID'][i]
        gold = gold_map[ID]
        true_syn = gold['syndrome']
        true_dis = gold['disease']

        # 处理 syndrome 多标签预测
        prob = probs_syn[i]
        max_prob, max_index = torch.max(prob, dim=0)
        if max_prob < 0.5:
            pred_syn = [0] * 10
            pred_syn[max_index.item()] = 1
        else:
            pred_syn = (prob >= 0.5).int().tolist()

        all_pred_syn.append(pred_syn)
        syn_gold_vec = [0] * 10
        for idx in true_syn:
            syn_gold_vec[idx] = 1
        all_true_syn.append(syn_gold_vec)

        # 处理 disease 单标签预测
        pred_dis = torch.argmax(probs_dis[i]).item()
        all_pred_dis.append(pred_dis)
        all_true_dis.append(true_dis)

# ------------------------
# Step 6: 计算评估指标
# ------------------------
# syndrome accuracy
correct_tags = 0
total_true_tags = 0
for pred, true in zip(all_pred_syn, all_true_syn):
    for i in range(10):
        if true[i] == 1:
            total_true_tags += 1
            if pred[i] == 1:
                correct_tags += 1
syn_acc = correct_tags / total_true_tags if total_true_tags > 0 else 0

# disease accuracy
dis_acc = accuracy_score(all_true_dis, all_pred_dis)

print(f"Syndrome Accuracy: {syn_acc:.4f}")
print(f"Disease Accuracy: {dis_acc:.4f}")

task1_acc = 0.5 * (syn_acc + dis_acc)
print(f"Task 1 Overall Accuracy: {task1_acc:.4f}")
