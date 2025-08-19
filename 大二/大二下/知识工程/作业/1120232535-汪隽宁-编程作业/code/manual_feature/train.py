from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MultiLabelBinarizer
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.multioutput import MultiOutputClassifier
from sklearn.metrics import accuracy_score, f1_score, precision_score, recall_score, hamming_loss
from sklearn.model_selection import GridSearchCV
import warnings
from utils_mf import calculate_symptom_recall_per_sample, load_data, load_test_data

# 忽略UserWarning，因为MultiLabelBinarizer在某些情况下可能发出警告
warnings.filterwarnings("ignore", category=UserWarning)


# --- 3. 加载数据集 ---
print("\nLoading data...")
X_train_full, y_syndrome_full, y_disease_full = load_data('./data/train_val.json')
X_test_eval, y_syndrome_test_eval, y_disease_test_eval = load_test_data('./data/test_input.json', './data/test_output.json')

print(f"Full training data shape: {X_train_full.shape}")
print(f"Evaluation test data shape: {X_test_eval.shape}")



# --- 4. 数据预处理 for Syndrome (多标签分类) ---
# MultiLabelBinarizer用于将多标签列表转换为二值矩阵
mlb = MultiLabelBinarizer(classes=range(10)) # 10个类别，0-9
y_syndrome_binarized_full = mlb.fit_transform(y_syndrome_full)
y_syndrome_binarized_test_eval = mlb.transform(y_syndrome_test_eval)



# --- 5. 划分训练集和验证集 ---
X_train, X_val, y_syndrome_train, y_syndrome_val, y_disease_train, y_disease_val = \
    train_test_split(X_train_full, y_syndrome_binarized_full, y_disease_full, 
                     test_size=0.2, random_state=42) # 80%训练，20%验证

print(f"Training data shape (after split): {X_train.shape}")
print(f"Validation data shape: {X_val.shape}")



# --- 6. Syndrome 多标签分类模型训练与评估 ---
print("\n--- 训练症状多分类器 ---")
syndrome_classifier = MultiOutputClassifier(RandomForestClassifier(n_estimators=100, random_state=42))

syndrome_classifier.fit(X_train, y_syndrome_train)

# 验证集评估
y_syndrome_val_pred = syndrome_classifier.predict(X_val)
y_syndrome_val_proba = syndrome_classifier.predict_proba(X_val) # 如果需要概率


acc = calculate_symptom_recall_per_sample(y_syndrome_val, y_syndrome_val_pred)
print(f"验证集正确率: {acc:.4f}")


# 测试集评估
y_syndrome_test_pred = syndrome_classifier.predict(X_test_eval)
y_syndrome_test_proba = syndrome_classifier.predict_proba(X_test_eval)

acc_syndrome = calculate_symptom_recall_per_sample(y_syndrome_binarized_test_eval, y_syndrome_test_pred)
print(f"测试集正确率: {acc_syndrome:.4f}")


# --- 7. Disease 单分类模型训练与评估 ---
print("\n--- 训练疾病单分类器 ---")
# disease_classifier = LogisticRegression(solver='liblinear', random_state=42, C=1.0)
disease_classifier = RandomForestClassifier(n_estimators=100, random_state=42, class_weight='balanced') 

disease_classifier.fit(X_train, y_disease_train)

# 验证集评估
y_disease_val_pred = disease_classifier.predict(X_val)

print(f"验证集正确率: {accuracy_score(y_disease_val, y_disease_val_pred):.4f}")

# 测试集评估
y_disease_test_pred = disease_classifier.predict(X_test_eval)
acc_disease = accuracy_score(y_disease_test_eval, y_disease_test_pred)
print(f"测试集正确率: {accuracy_score(y_disease_test_eval, y_disease_test_pred):.4f}")

print(f"\nTask 1 acc = {0.5 * (acc_syndrome + acc_disease):.4f}")

# --- 8. 超参数调优 ---
# 8.0 定义超参数网格
param_grid_syndrome = {
    'estimator__n_estimators': [100, 200, 500, 1000],
    'estimator__max_depth': [10, 20, 30, 50, 100],
    'estimator__min_samples_split': [2, 5, 10],
    'estimator__min_samples_leaf': [1, 2, 4],
    'estimator__max_features': ['sqrt', 'log2', None],
    'estimator__bootstrap': [True, False],
    'estimator__class_weight': [None, 'balanced']
}

param_grid_disease = {
    'n_estimators': [100, 200, 500, 1000],  # 森林中树的数量
    'max_depth': [10, 20, 30, 50, 100],  # 每棵树的最大深度
    'min_samples_split': [2, 5, 10],  # 内部节点再划分所需最小样本数
    'min_samples_leaf': [1, 2, 4],  # 叶子节点最小样本数
    'max_features': ['sqrt', 'log2', None],  # 特征选择策略
    'bootstrap': [True, False],  # 是否有放回采样   
    'class_weight': [None, 'balanced']  # 是否平衡类别权重（适合处理类别不均衡）
}



# 8.1 症状分类器的超参数调优
syndrome_classifier_tuned = MultiOutputClassifier(RandomForestClassifier(random_state=42))
grid_search = GridSearchCV(syndrome_classifier_tuned, param_grid_syndrome, 
                           scoring='accuracy', cv=3, verbose=2, n_jobs=-1)
grid_search.fit(X_train, y_syndrome_train)

print("\nBest parameters found for Syndrome classifier:")
print(grid_search.best_params_)
best_model = grid_search.best_estimator_

# 使用最佳模型进行预测
y_syndrome_test_pred = best_model.predict(X_test_eval)
acc_syndrome = calculate_symptom_recall_per_sample(y_syndrome_binarized_test_eval, y_syndrome_test_pred)
print(f"调优后，症状测试集正确率: {acc_syndrome:.4f}")


# 8.2 疾病分类器的超参数调优
disease_classifier_tuned = RandomForestClassifier(random_state=42)
grid_search_disease = GridSearchCV(disease_classifier_tuned, param_grid_disease, 
                                    scoring='accuracy', cv=3, verbose=2, n_jobs=-1)
grid_search_disease.fit(X_train, y_disease_train)
print("\nBest parameters found for Disease classifier:")
print(grid_search_disease.best_params_)
best_model_disease = grid_search_disease.best_estimator_
# 使用最佳模型进行预测
y_disease_test_pred = best_model_disease.predict(X_test_eval)
acc_disease = accuracy_score(y_disease_test_eval, y_disease_test_pred)
print(f"调优后，疾病测试集正确率: {acc_disease:.4f}")

print(f"\nTask 1 acc (after tuning) = {0.5 * (acc_syndrome + acc_disease):.4f}")