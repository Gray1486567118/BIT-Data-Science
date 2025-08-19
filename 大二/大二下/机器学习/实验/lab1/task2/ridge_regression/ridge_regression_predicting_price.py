import ridge_regression
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split

data = fetch_california_housing(data_home='./data')
Xtrain, Xtest, ytrain, ytest = train_test_split(data.data, data.target, test_size=0.2, random_state=42)

ridge_regressor = ridge_regression.RidgeRegression(l2reg=0.1)
ridge_regressor.fit(Xtrain, ytrain)

y_pred = ridge_regressor.predict(Xtest)
mse = ridge_regressor.score(Xtest, ytest)
print("Current l2reg: 0.1")
print(f"MSE: {mse}")



grid_search, _ = ridge_regression.do_grid_search_ridge(Xtrain, ytrain, Xtest, ytest)
optimized_mse = -grid_search.score(Xtest, ytest)
print(f"\nOptimized l2reg: {grid_search.best_params_['l2reg']}")
print(f"Optimized MSE: {optimized_mse}")