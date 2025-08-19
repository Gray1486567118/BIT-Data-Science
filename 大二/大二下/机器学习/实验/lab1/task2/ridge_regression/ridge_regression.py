"""
Ridge regression using scipy's minimize function and demonstrating the use of
sklearn's framework.
"""
from sklearn.base import BaseEstimator, RegressorMixin
from scipy.optimize import minimize
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import GridSearchCV, PredefinedSplit
from sklearn.model_selection import ParameterGrid
from sklearn.metrics import mean_squared_error, make_scorer
import pandas as pd
from sklearn.metrics import confusion_matrix
import itertools

from setup_problem import load_problem


class RidgeRegression(BaseEstimator, RegressorMixin):
    """ ridge regression"""
    def __init__(self, l2reg=1):
        if l2reg < 0:
            raise ValueError('Regularization penalty should be at least 0.')
        self.l2reg = l2reg
        self.w_ = None
        self.n_samples = None
        self.n_features = None
        

    def fit(self, X, y=None):
        """
        拟合 Ridge 回归模型。
        参数:
        - X: 特征矩阵。
        - y: 目标值向量。
        实现步骤:
        1. 获取样本数量和特征数量。
        2. 将 y 转换为一维数组。
        3. 定义 Ridge 回归的目标函数，包括经验风险和 L2 正则化项。
        4. 使用 scipy.optimize.minimize 优化目标函数，求解权重向量 w。
        提示：步骤3可以通过定义一个ridge_obj函数实现，可能实现如下：
         # 计算预测值，即线性模型的输出，X 为输入特征矩阵，w 为权重向量
         # 计算残差，即实际值 y 与预测值 predictions 之间的差异
         # 计算经验风险，使用残差的平方和除以样本数量 n，得到均方误差
         # 计算 L2 正则化项，即权重向量 w 的平方和
         # 计算目标函数值，即经验风险加上 L2 正则化项乘以正则化参数 self.l2reg
         # 返回目标函数值
        """

        # 此处补充代码
        # 1. 获取样本数量和特征数量
        self.n_samples, self.n_features = X.shape

        # 2. 将 y 转换为一维数组
        y = np.asarray(y).flatten()
        
        # 3. 定义 Ridge 回归的目标函数
        def ridge_obj(w):
            predictions = X @ w
            residuals = y - predictions
            mse = np.sum(residuals**2) / self.n_samples
            l2 = np.sum(w**2)
            return mse + self.l2reg * l2

        # 4. 使用 scipy.optimize.minimize 优化目标函数
        w0 = np.zeros(self.n_features)
        result = minimize(ridge_obj, w0, method='L-BFGS-B')
        self.w_ = result.x
    
        return self

        
    def predict(self, X, y=None):
        """
        使用训练好的模型进行预测。
        参数:
        - X: 特征矩阵。
        返回:
        - 预测值向量。
        实现步骤:
        1. 检查模型是否已经训练。（提示：try ... except...实现）
        2. 计算并返回预测值。
        """
        try:
            return X @ self.w_
        except AttributeError:
            raise ValueError("Model is not fitted yet. Please call 'fit' before 'predict'.")
        
       
       
    def score(self, X, y):
        """
        计算模型的平均平方误差（MSE）。
        参数:
        - X: 特征矩阵。
        - y: 目标值向量。
        返回:
        - MSE 值。
        实现步骤:
        1. 检查模型是否已经训练。（提示：try ... except...实现）
        2. 计算预测值。
        3. 计算并返回残差的平方和除以样本数量。
        """
        try:
            predictions = self.predict(X)
            residuals = y - predictions
            mse = np.sum(residuals**2) / X.shape[0]
            return mse
        except AttributeError:
            raise ValueError("Model is not fitted yet. Please call 'fit' before 'score'.")


def compare_our_ridge_with_sklearn(X_train, y_train, l2_reg=1):
    """
    比较自定义的 Ridge 回归与 sklearn 的 Ridge 回归。
    参数:
    - X_train: 训练特征矩阵。
    - y_train: 训练目标值向量。
    - l2_reg: L2 正则化参数。
    返回：
    - 返回两个模型系数差的平方和
    实现步骤:
    1. 使用 sklearn 的 Ridge 回归拟合数据并提取系数。
    2. 使用自定义的 Ridge 回归拟合数据并提取系数。
    3. 比较两个模型的系数差异。
    """
    # 使用 sklearn 的 Ridge 回归拟合数据
    from sklearn.linear_model import Ridge
    ridge_sklearn = Ridge(alpha=l2_reg)
    ridge_sklearn.fit(X_train, y_train)
    coefs_sklearn = ridge_sklearn.coef_

    # 使用自定义的 Ridge 回归拟合数据
    ridge_our = RidgeRegression(l2reg=l2_reg)
    ridge_our.fit(X_train, y_train)
    coefs_our = ridge_our.w_

    # 比较两个模型的系数差异
    diff = np.sum((coefs_sklearn - coefs_our)**2)
    
    return diff


def do_grid_search_ridge(X_train, y_train, X_val, y_val):
    """
    使用网格搜索进行超参数调优。
    参数:
    - X_train: 训练特征矩阵。
    - y_train: 训练目标值向量。
    - X_val: 验证特征矩阵。
    - y_val: 验证目标值向量。
    返回：
    - 网格搜索结果和性能指标
    实现步骤:
    1. 将训练集和验证集组合，并创建索引标识验证集。
    2. 定义 L2 正则化参数的搜索范围。
    3. 使用 GridSearchCV 进行网格搜索，找到最佳超参数。
    4. 返回网格搜索结果和性能指标。
    """

    # 使用 sklearn 来进行超参数调优
    # 默认情况下，GridSearchCV.fit 会自动将数据分成训练集和验证集；
    # 我们使用自己的数据划分方式，所以需要将训练集和验证集堆叠在一起，
    # 并提供一个索引（validation_fold）来指定哪些条目是训练集，哪些是验证集。
    X_train_val = np.vstack((X_train, X_val))
    y_train_val = np.concatenate((y_train, y_val))
    val_fold = [-1] * len(X_train) + [0] * len(X_val)  # 0 corresponds to validation

    
    # 现在我们设置并进行 L2 正则化参数（l2reg）的网格搜索。np.concatenate 
    # 命令展示了我寻找最佳超参数的过程。在每一行中，我都在先前网格中
    # 发现的一个有前景的超参数范围内进行精细调整。
    # 当性能作为超参数的函数是凸形的时，这种方法效果比较好，（在本实验中）。
    param_grid = [{
        'l2reg':
        np.unique(
            np.concatenate((10.**np.arange(-6, 1, 1), np.arange(1, 3, .3))))
    }]

    ridge_regression_estimator = RidgeRegression()
    
    
    # 此处调用GridSearchCV实现
    grid_search = GridSearchCV(
        ridge_regression_estimator,
        param_grid,
        scoring=make_scorer(mean_squared_error, greater_is_better=False),
        cv=PredefinedSplit(val_fold),
        verbose=0,
        n_jobs=-1,
    )

    grid_search.fit(X_train_val, y_train_val)

    results_df = pd.DataFrame(grid_search.cv_results_)

    return grid_search, results_df
    

def plot_prediction_functions(x, pred_fns, x_train, y_train,
                              legend_loc="best"):
    # Assumes pred_fns is a list of dicts, and each dict has a "name" key and a
    # "preds" key. The value corresponding to the "preds" key is an array of
    # predictions corresponding to the input vector x. x_train and y_train are
    # the input and output values for the training data
    fig, ax = plt.subplots(figsize=(10, 8))
    ax.set_xlabel('Input Space: [0,1)')
    ax.set_ylabel('Action/Outcome Space')
    ax.set_title("Prediction Functions")
    
    # 填充代码对岭回归的结果进行可视化

    ax.scatter(x_train, y_train, color='black', label='Training Data')

    for fn in pred_fns:
        ax.plot(x, fn["preds"], label=fn["name"])  # 预测曲线

    ax.legend(loc=legend_loc)  # 添加图例

    return fig


def main():
    lasso_data_fname = "lasso_data.pickle"
    x_train, y_train, x_val, y_val, target_fn, coefs_true, featurize = load_problem(lasso_data_fname)

    # 获取特征
    X_train = featurize(x_train)
    X_val = featurize(x_val)

    
    # 对比sklearn
    compare_our_ridge_with_sklearn(X_train, y_train, l2_reg=1.5)

    # 超参数调优
    grid, results = do_grid_search_ridge(X_train, y_train, X_val, y_val)
    print(results)


    # 可视化，证性能与正则化参数

    fig, ax = plt.subplots()
    ax.semilogx(results["param_l2reg"], results["mean_test_score"])
    ax.grid()
    ax.set_title("Validation Performance vs L2 Regularization")
    ax.set_xlabel("L2-Penalty Regularization Parameter")
    ax.set_ylabel("Mean Squared Error")
    fig.show()
    

    # 可视化，绘制预测函数，并比较几个拟合函数和目标函数的系数
    pred_fns = []
    x = np.sort(np.concatenate([np.arange(0, 1, .001), x_train]))
    name = "Target Parameter Values (i.e. Bayes Optimal)"
    pred_fns.append({"name": name, "coefs": coefs_true, "preds": target_fn(x)})

    l2regs = [0, grid.best_params_['l2reg'], 1]
    X = featurize(x)
    for l2reg in l2regs:
        ridge_regression_estimator = RidgeRegression(l2reg=l2reg)
        ridge_regression_estimator.fit(X_train, y_train)
        name = "Ridge with L2Reg=" + str(l2reg)
        pred_fns.append({
            "name": name,
            "coefs": ridge_regression_estimator.w_,
            "preds": ridge_regression_estimator.predict(X)
        })

    f = plot_prediction_functions(x,
                                  pred_fns,
                                  x_train,
                                  y_train,
                                  legend_loc="best")
    f.show()


   
if __name__ == '__main__':
    main()
