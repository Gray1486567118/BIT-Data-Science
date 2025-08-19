import torch
from torch.utils.data import Dataset
import json

class TCMNumericDataset(Dataset):
    def __init__(self, data_list, num_disease_labels=4, num_syndrome_labels=10):
        self.data = data_list
        self.num_disease_labels = num_disease_labels
        self.num_syndrome_labels = num_syndrome_labels

        # 确定特征维度
        if data_list:
            sample_item = data_list[0]
            self.face_dim = len(sample_item.get("face_vec", []))
            self.tongue_dim = len(sample_item.get("tongue_vec", []))
            self.pulse_dim = len(sample_item.get("pulse_vec", []))
            self.main_symptoms_dim = len(sample_item.get("main_symptoms", []))
            self.input_dim = self.face_dim + self.tongue_dim + self.pulse_dim + self.main_symptoms_dim
            print(f"Detected input dimensions: Face={self.face_dim}, Tongue={self.tongue_dim}, Pulse={self.pulse_dim}, MainSymptoms={self.main_symptoms_dim}")
            print(f"Total input dimension for NN: {self.input_dim}")
        else:
            self.input_dim = 0
            print("Warning: Dataset is empty, input dimension not determined.")

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        item = self.data[idx]

        # 组合所有特征向量
        features = []
        features.extend(item.get("face_vec", []) or [0.0] * self.face_dim)
        features.extend(item.get("tongue_vec", []) or [0.0] * self.tongue_dim)
        features.extend(item.get("pulse_vec", []) or [0.0] * self.pulse_dim)
        features.extend(item.get("main_symptoms", []) or [0.0] * self.main_symptoms_dim)
        
        # 转换为float32张量
        features_tensor = torch.tensor(features, dtype=torch.float32)

        # disease 单标签
        disease_labels = None
        if "disease" in item and item["disease"] is not None:
            disease_labels = torch.tensor(item["disease"], dtype=torch.long)
        
        # syndrome 多分类
        syndrome_labels = None
        if "syndrome" in item and item["syndrome"] is not None:
            syndrome_labels_tensor = torch.zeros(self.num_syndrome_labels, dtype=torch.float32)
            for label_idx in item["syndrome"]:
                if 0 <= label_idx < self.num_syndrome_labels:
                    syndrome_labels_tensor[label_idx] = 1.0
            syndrome_labels = syndrome_labels_tensor

        return {
            "features": features_tensor,
            "disease_labels": disease_labels,
            "syndrome_labels": syndrome_labels,
            "ID": item["ID"]
        }


def read_json(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        return json.load(f)