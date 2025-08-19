import random
import numpy as np
import torch
from sklearn.metrics import f1_score, accuracy_score


def set_seed(seed: int):
    """固定随机种子，保证可复现"""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)


def compute_metrics(pred):
    """
    HF Trainer 回调：接收 preds 和 labels，返回 dict{metric: value}
    preds.label_ids 是一个 tuple: ([syn_labels],[dis_labels])
    preds.predictions 是一个 tuple: ([syn_logits],[dis_logits])
    """
    logits_syn, logits_dis = pred.predictions
    labels_syn, labels_dis = pred.label_ids

    # 多标签 f1_score
    pred_syn = (torch.sigmoid(torch.tensor(logits_syn)) > 0.5).int().numpy()
    f1 = f1_score(labels_syn, pred_syn, average='micro')
    # syn_accuracy = np.sum(np.logical_and(labels_syn, pred_syn)) / np.sum(labels_syn)  # jaccard

    # 单标签accuracy
    pred_dis = np.argmax(logits_dis, axis=1)
    acc = accuracy_score(labels_dis, pred_dis)

    print(f"F1 Score (Syndrome): {f1:.4f}, Accuracy (Disease): {acc:.4f}")

    return {
        'f1_syndrome': f1,
        # 'syn_accuracy': syn_accuracy,
        'acc_disease': acc
    }