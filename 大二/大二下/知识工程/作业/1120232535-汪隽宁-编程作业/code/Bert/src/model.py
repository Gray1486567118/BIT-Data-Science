import torch
import torch.nn as nn
from transformers import BertPreTrainedModel, BertModel

class BertForTCM(BertPreTrainedModel):
    """
    在 BertModel 基础上，额外添加两个分类头：
    1) 10 维多标签（证型）
    2) 4 维单标签（疾病）
    """
    def __init__(self, config):
        super().__init__(config)
        struct_dim = 63  # face(6) + tongue(8) + pulse(16) + main_symptoms(33) = 63

        # 主干 BERT
        self.bert = BertModel(config)
        hidden_size = config.hidden_size + struct_dim # 768 for bert-base + 30 for struct_dim
        

        # 多标签
        self.classifier_syndrome = nn.Sequential(
            nn.Linear(hidden_size, 256),
            nn.ReLU(),
            nn.Linear(256, 10)
        )
        
        # 单标签
        self.classifier_disease = nn.Sequential(
            nn.Linear(hidden_size, 128),
            nn.ReLU(),
            nn.Linear(128, 4)
        )

        # 初始化权重
        self.init_weights()

    def forward(self,
                input_ids,
                attention_mask,
                labels_syndrome=None,
                label_disease=None,
                struct_feat=None):
        # BERT 编码
        outputs = self.bert(
            input_ids=input_ids,
            attention_mask=attention_mask
        )

        pooled = outputs.pooler_output

        # 拼接特征工程
        if struct_feat is not None:
            pooled = torch.cat([pooled, struct_feat], dim=1)

        # 预测
        logits_syn = self.classifier_syndrome(pooled)   # [batch,10]
        logits_dis = self.classifier_disease(pooled)    # [batch,4]


        loss = None
        if labels_syndrome is not None and label_disease is not None:
            # 计算多标签 loss
            loss_fct_syn = nn.BCEWithLogitsLoss()
            l_syn = loss_fct_syn(logits_syn, labels_syndrome)
            # 计算单标签 loss
            loss_fct_dis = nn.CrossEntropyLoss()
            l_dis = loss_fct_dis(logits_dis, label_disease)    
            loss = l_syn + l_dis
        #
        return {
            'loss': loss,
            'logits_syndrome': logits_syn,
            'logits_disease':  logits_dis
        }