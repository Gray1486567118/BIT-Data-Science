# dataset.py

from torch.utils.data import Dataset
from transformers import AutoTokenizer
import torch

class TCMDataset(Dataset):
    def __init__(self, data, tokenizer, max_length=512, mode="train"):
        self.data = data
        self.tokenizer = tokenizer
        self.max_length = max_length
        self.mode = mode
        self.num_syndrome_labels = 10   # 共10种症状标签

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        item = self.data[idx]
        
        # ✅ 确保 tokenizer 返回 attention_mask
        encoding = self.tokenizer(
            item["text"],
            max_length=self.max_length,
            truncation=True,
            padding="max_length",
            return_tensors="pt",
            return_attention_mask=True,  # 必须返回 attention_mask
        )
        

        if self.mode == "train":
            disease_labels = torch.tensor(item["disease"], dtype=torch.long)
            syndrome_labels = torch.zeros(self.num_syndrome_labels, dtype=torch.float)
            for label_idx in item["syndrome"]:
                if label_idx < self.num_syndrome_labels: # 确保索引在范围内
                    syndrome_labels[label_idx] = 1.0 # 设置对应索引为1
            encoding["disease_labels"] = disease_labels
            encoding["syndrome_labels"] = syndrome_labels


        encoding = {k: v.squeeze(0) for k, v in encoding.items()}
        return encoding
    
    
class PredictionDataset(Dataset):
    def __init__(self, data, tokenizer, max_length=2048):
        self.data = data
        self.tokenizer = tokenizer
        self.max_length = max_length

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        item = self.data[idx]
        
        # 对于预测，我们只关心输入文本，不需要标签
        encoding = self.tokenizer(
            item["text"],
            max_length=self.max_length,
            truncation=True,
            padding="max_length", # 保持与训练时的padding方式一致
            return_tensors="pt",
            return_attention_mask=True,
        )
        
        # 去除 batch 维度 (squeeze(0))
        encoding = {k: v.squeeze(0) for k, v in encoding.items()}
        
        # ⚠️ 这里不返回 'labels'
        return encoding