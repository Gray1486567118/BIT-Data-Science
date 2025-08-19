import json
import torch
from torch.utils.data import Dataset
from transformers import BertTokenizerFast, AutoTokenizer

SYNDROME_LIST = [
    '气虚血瘀证', '痰瘀互结证', '气阴两虚证', '气滞血瘀证',
    '肝阳上亢证', '阴虚阳亢证', '痰热蕴结证', '痰湿痹阻证',
    '阳虚水停证', '肝肾阴虚证'
]
DISEASE_LIST = ['胸痹心痛病', '心衰病', '眩晕病', '心悸病']


class TCMDataset(Dataset):
    def __init__(self, path, tokenizer_name, max_length, mode='train'):
        super().__init__()
        self.samples = json.load(open(path, 'r', encoding='utf-8'))
        self.tokenizer = BertTokenizerFast.from_pretrained(tokenizer_name)
        self.max_length = max_length
        self.mode = mode  # 'train' or 'test'

    def __len__(self):
        return len(self.samples)

    def __getitem__(self, idx):
        item = self.samples[idx]
        text = item['text']

        # 分词 + 截断 + 填充
        enc = self.tokenizer.encode_plus(
            text,
            truncation=True,
            max_length=self.max_length,
            add_special_tokens=True,
            return_attention_mask=True,
            padding='max_length',
            return_tensors='pt',
            # return_token_type_ids=False # Qwen tokenizer 不需要 token_type_ids
        )

        face = torch.tensor(item.get("face_vec", []), dtype=torch.float)
        tongue = torch.tensor(item.get("tongue_vec", []), dtype=torch.float)
        pulse = torch.tensor(item.get("pulse_vec", []), dtype=torch.float)
        main_symptoms = torch.tensor(item.get("main_symptoms", []), dtype=torch.float)
        struct_feat = torch.cat([face, tongue, pulse, main_symptoms], dim=0)

        # 基础返回字段
        data = {
            'input_ids':    enc['input_ids'].squeeze(0),
            'attention_mask': enc['attention_mask'].squeeze(0),
            'struct_feat':  struct_feat
        }
        
        if self.mode != 'test':
            # 构造 multi-hot 向量: [10]
            syn_idx = item['syndrome']  # 索引列表
            syn = torch.zeros(len(SYNDROME_LIST), dtype=torch.float)
            syn[syn_idx] = 1.0
            # 单标签 disease
            dis = torch.tensor(item['disease'], dtype=torch.long)
            data.update({
                'labels_syndrome': syn,
                'label_disease':   dis
            })
        else:
            # 测试时只需 ID
            data['ID'] = item['ID']


        return data    
