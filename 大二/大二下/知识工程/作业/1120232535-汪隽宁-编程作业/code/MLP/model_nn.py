import torch
import torch.nn as nn

class MultiTaskNN(nn.Module):
    def __init__(self, input_dim, num_disease_labels, num_syndrome_labels, hidden_dim=128, dropout_prob=0.3):
        super(MultiTaskNN, self).__init__()
        self.input_dim = input_dim
        self.num_disease_labels = num_disease_labels
        self.num_syndrome_labels = num_syndrome_labels
        self.hidden_dim = hidden_dim
        self.dropout_prob = dropout_prob

        # 共享特征提取层
        self.feature_extractor = nn.Sequential(
            nn.Linear(input_dim, hidden_dim * 2), 
            nn.ReLU(),
            nn.Dropout(self.dropout_prob),
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.ReLU(),
            nn.Dropout(self.dropout_prob)
        )

        # Disease 分类头 (单分类)
        self.disease_classifier = nn.Linear(hidden_dim, num_disease_labels)

        # Syndrome 分类头 (多标签分类)
        self.syndrome_classifier = nn.Linear(hidden_dim, num_syndrome_labels)

    def forward(self, features, disease_labels=None, syndrome_labels=None):
        # 提取共享特征
        shared_features = self.feature_extractor(features)

        # 分别计算两个任务的 logits
        disease_logits = self.disease_classifier(shared_features)
        syndrome_logits = self.syndrome_classifier(shared_features)

        total_loss = None
        if disease_labels is not None and syndrome_labels is not None:
            # Disease 损失：交叉熵
            disease_loss_fn = nn.CrossEntropyLoss()
            disease_loss = disease_loss_fn(disease_logits, disease_labels)

            # Syndrome 损失：二元交叉熵
            syndrome_loss_fn = nn.BCEWithLogitsLoss()
            syndrome_loss = syndrome_loss_fn(syndrome_logits, syndrome_labels)
            
            # 总损失
            total_loss = disease_loss + syndrome_loss
        
        return {
            "loss": total_loss,
            "disease_logits": disease_logits,
            "syndrome_logits": syndrome_logits,
        }