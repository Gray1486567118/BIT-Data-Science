## 实验任务
1. 使用分类模型（MLPClassifier）完成对手写数字的分类(load_digits)，并使用评测指标precision_score、recall_score、f1_score对分类结果评测
2. 使用回归模型（MLPRegressor）实现对波士顿房价的预测(load_boston)，并使用 r2-score 对回归结果评测
3. 实现自定义神经网络回归模型，实现对自定义数据(lasso_data)的预测

## 实验要求和评分标准

- 完成实验中的3个项任务（前两个3分，后一个4分）
- 加分项：
    - 使用GridSearchCV对实验任务一的分类模型调参，并将最佳参数和评分结果输出。（1分）
    - 在实验任务一中采用不同激活函数（identity, logistic, tanh, relu）训练模型，并将评分结果输出。（1分）
    - 任意选取load_boston 数据集中的2个特征，分别绘制部分依赖图（使用plot_partial_dependence）。（1分）