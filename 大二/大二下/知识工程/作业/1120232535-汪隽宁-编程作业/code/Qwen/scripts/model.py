# model.py

import torch
import torch.nn as nn
from transformers import AutoModel, AutoConfig, PreTrainedModel

class QwenForTCM(PreTrainedModel):  
    def __init__(self, config):
        super().__init__(config)
        self.backbone = AutoModel.from_pretrained(config._name_or_path, config=config)
        self.dropout = nn.Dropout(0.1)
        self.disease_classifier = nn.Sequential(
            nn.Linear(self.backbone.config.hidden_size, self.backbone.config.hidden_size // 2),
            nn.ReLU(),
            nn.Dropout(0.1),
            nn.Linear(self.backbone.config.hidden_size // 2, config.num_labels)
        )

        self.syndrome_classifier = nn.Sequential(
            nn.Linear(self.backbone.config.hidden_size, self.backbone.config.hidden_size // 2),
            nn.ReLU(),
            nn.Dropout(0.1),
            nn.Linear(self.backbone.config.hidden_size // 2, 10)
        )
        
        self.post_init()  # ✅ 初始化权重，否则 load 权重时会失败

    def forward(self, input_ids, attention_mask=None, disease_labels=None, syndrome_labels=None):
        outputs = self.backbone(input_ids=input_ids, attention_mask=attention_mask)
        
        last_token_indices = torch.sum(attention_mask, dim=1) - 1
        batch_size, sequence_length, hidden_size = outputs.last_hidden_state.shape
        expanded_last_token_indices = last_token_indices.unsqueeze(-1).unsqueeze(-1).expand(batch_size, 1, hidden_size)
        sequence_output = torch.gather(outputs.last_hidden_state, 1, expanded_last_token_indices).squeeze(1) # [CLS] token

        pooled_output = self.dropout(sequence_output)

        # 计算分类 logits
        disease_logits = self.disease_classifier(pooled_output)
        syndrome_logits = self.syndrome_classifier(pooled_output)


        total_loss = None

        if disease_labels is not None and syndrome_labels is not None:
            # Disease loss
            disease_loss_fn = nn.CrossEntropyLoss()
            disease_loss = disease_loss_fn(disease_logits, disease_labels)

            # Syndrome loss
            syndrome_loss_fn = nn.BCEWithLogitsLoss() 
            syndrome_loss = syndrome_loss_fn(syndrome_logits, syndrome_labels)

            total_loss = disease_loss + syndrome_loss
            
            return {
                "loss": total_loss,
                "disease_logits": disease_logits,
                "syndrome_logits": syndrome_logits,
            }
        elif disease_labels is not None: # disease 单任务
             disease_loss_fn = nn.CrossEntropyLoss()
             disease_loss = disease_loss_fn(disease_logits, disease_labels)
             return {
                "loss": disease_loss,
                "disease_logits": disease_logits,
                "syndrome_logits": syndrome_logits,
            }
        elif syndrome_labels is not None: # syndrome 单任务
            syndrome_loss_fn = nn.BCEWithLogitsLoss()
            syndrome_loss = syndrome_loss_fn(syndrome_logits, syndrome_labels)
            return {
                "loss": syndrome_loss,
                "disease_logits": disease_logits,
                "syndrome_logits": syndrome_logits,
            }
        else: # 预测
            return {
                "disease_logits": disease_logits,
                "syndrome_logits": syndrome_logits,
            }
