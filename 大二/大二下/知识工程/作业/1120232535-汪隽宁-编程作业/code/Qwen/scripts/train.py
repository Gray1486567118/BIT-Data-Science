# train.py

from transformers import AutoTokenizer, AutoConfig
from transformers import Trainer, TrainingArguments
from dataset import TCMDataset
from model import QwenForTCM
import torch
import yaml
from utils import read_json, compute_metrics

# --- 0. 读取配置文件 ---
with open("config.yaml", "r", encoding="utf-8") as f:
    cfg = yaml.safe_load(f)

# --- 1. 设置参数 ---、
model_name = cfg['model_name']

# --- 2. 加载分词器 ---
tokenizer = AutoTokenizer.from_pretrained(model_name)
tokenizer.pad_token = tokenizer.eos_token

# --- 3. 准备数据集 ---
# 读取数据
# train_data = read_json(cfg['train_path'])
# val_data = read_json(cfg['val_path'])
train_val_data = read_json(cfg['train_val_path'])

# 转化为 Hugging Face 的 Dataset 格式
# train_dataset = TCMDataset(train_data, tokenizer)
# val_dataset = TCMDataset(val_data, tokenizer)
train_val_dataset = TCMDataset(train_val_data, tokenizer)

# --- 4. 加载模型 ---
config = AutoConfig.from_pretrained(model_name)
config.num_labels = 4
model = QwenForTCM(config)  
model = model.to(torch.float32)


# --- 5. 定义训练参数 ---
training_args = TrainingArguments(
    output_dir=cfg['save_path'],
    num_train_epochs=cfg['epochs'],
    learning_rate=5e-5,
    lr_scheduler_type="cosine",
    per_device_train_batch_size=cfg['per_device_train_batch_size'],
    per_device_eval_batch_size=cfg['per_device_eval_batch_size'],
    warmup_steps=cfg['warmup_steps'],                  # 预热步数
    weight_decay=cfg['weight_decay'],                  # 权重衰减

    logging_dir="./logs",
    # eval_strategy="epoch",
    eval_strategy="no",
    save_strategy="epoch",
    save_total_limit=1,
)


# --- 6. 定义 Trainer ---
trainer = Trainer(
    model=model,
    args=training_args,
    # train_dataset=train_dataset,
    train_dataset=train_val_dataset,
    eval_dataset=None,
    tokenizer=tokenizer,
    compute_metrics=compute_metrics,  # 多任务评估指标
)

# --- 7. 开始训练 ---
trainer.train()

# --- 8. 保存模型和分词器 ---
save_path = cfg['save_path']

model.save_pretrained(save_path)
tokenizer.save_pretrained(save_path)