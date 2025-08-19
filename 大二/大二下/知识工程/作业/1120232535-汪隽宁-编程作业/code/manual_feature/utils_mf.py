import numpy as np
import json


# --- 1. 数据加载函数 ---
def load_data(json_file):
    """
    加载JSON数据文件并解析特征和标签。
    """

    with open(json_file, 'r', encoding='utf-8') as f:
        data = json.load(f)

    features_list = []
    syndromes_list = []
    diseases_list = []

    
    for item in data:
        # 合并所有特征向量
        combined_features = []
        combined_features.extend(item.get('face_vec', []))
        combined_features.extend(item.get('tongue_vec', []))
        combined_features.extend(item.get('pulse_vec', []))
        combined_features.extend(item.get('main_symptoms', []))
        
        features_list.append(combined_features)
        syndromes_list.append(item.get('syndrome', []))
        diseases_list.append(item.get('disease', -1)) # -1作为默认值，以防数据缺失

    # 转换为numpy数组
    X = np.array(features_list)
    y_syndrome = syndromes_list
    y_disease = np.array(diseases_list)
    
    return X, y_syndrome, y_disease

def load_test_data(test_input_file, test_output_file):
    """
    加载测试集的输入特征和输出标签。
    """

    with open(test_input_file, 'r', encoding='utf-8') as f_input:
        input_data = json.load(f_input)
    with open(test_output_file, 'r', encoding='utf-8') as f_output:
        output_data = json.load(f_output)
    
    X_test_features = []
    y_syndrome_test_output = []
    y_disease_test_output = []

    for item in input_data:
        combined_features = []
        combined_features.extend(item.get('face_vec', []))
        combined_features.extend(item.get('tongue_vec', []))
        combined_features.extend(item.get('pulse_vec', []))
        combined_features.extend(item.get('main_symptoms', []))
        X_test_features.append(combined_features)
    

    for item in output_data:
        y_syndrome_test_output.append(item.get('syndrome', []))
        y_disease_test_output.append(item.get('disease', -1))

    return np.array(X_test_features), y_syndrome_test_output, np.array(y_disease_test_output)


# --- 新增：计算每个样本的症状召回率的平均值 ---
def calculate_symptom_recall_per_sample(y_true_binarized, y_pred_binarized):
    """
    计算 '预测对的症状标签数量 / 真实症状标签数量' 的平均值。
    这等价于每个样本的召回率的平均值。
    对于真实标签为空的样本，如果预测标签也为空，则该样本召回率为1；否则为0。
    """
    num_samples = y_true_binarized.shape[0]
    recalls = []

    for i in range(num_samples):
        true_labels_indices = np.where(y_true_binarized[i] == 1)[0]
        pred_labels_indices = np.where(y_pred_binarized[i] == 1)[0]

        # 转换为集合以便计算交集
        true_set = set(true_labels_indices)
        pred_set = set(pred_labels_indices)

        intersection_size = len(true_set.intersection(pred_set))
        recall = intersection_size / len(true_set)
        recalls.append(recall)
            
    return np.mean(recalls)