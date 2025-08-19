from sklearn.datasets import load_diabetes, load_wine
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.tree import DecisionTreeClassifier, DecisionTreeRegressor
from sklearn.ensemble import RandomForestClassifier, RandomForestRegressor
from sklearn.metrics import (
    accuracy_score, precision_score, recall_score,
    mean_squared_error, mean_absolute_error, median_absolute_error
)
import matplotlib.pyplot as plt
import numpy as np


def train_and_evaluate_model(model, param_grid, X_train, X_test, y_train, y_test, is_classification):
    scoring = 'accuracy' if is_classification else 'neg_mean_squared_error'
    grid_search = GridSearchCV(model, param_grid, cv=5, scoring=scoring)
    grid_search.fit(X_train, y_train)

    y_pred = grid_search.predict(X_test)

    if is_classification:
        acc = accuracy_score(y_test, y_pred)
        prec = precision_score(y_test, y_pred, average='weighted')
        rec = recall_score(y_test, y_pred, average='weighted')
        print(f"Accuracy: {acc:.4f}, Precision: {prec:.4f}, Recall: {rec:.4f}")
    else:
        mse = mean_squared_error(y_test, y_pred)
        mae = mean_absolute_error(y_test, y_pred)
        medae = median_absolute_error(y_test, y_pred)
        print(f"MSE: {mse:.2f}, MAE: {mae:.2f}, MedAE: {medae:.2f}")

    return grid_search.best_estimator_


def visualize_top2_features(model, X, y, feature_names, target_names=None, is_classification=True):
    importances = model.feature_importances_
    top2 = np.argsort(importances)[-2:]
    X_top2 = X[:, top2]

    if is_classification:
        for label in np.unique(y):
            plt.scatter(X_top2[y == label, 0], X_top2[y == label, 1], label=target_names[label], alpha=0.6)
        plt.xlabel(feature_names[top2[0]])
        plt.ylabel(feature_names[top2[1]])
        plt.title("Top 2 Feature Scatter (Classification)")
        plt.legend()
        plt.show()
    else:
        fig = plt.figure(figsize=(10, 6))
        ax = fig.add_subplot(111, projection='3d')
        ax.scatter(X_top2[:, 0], X_top2[:, 1], y, c=y, cmap='plasma')
        ax.set_xlabel(feature_names[top2[0]])
        ax.set_ylabel(feature_names[top2[1]])
        ax.set_zlabel("Target")
        plt.title("Top 2 Feature Scatter (Regression)")
        plt.show()


def run_wine_experiment(use_random_forest=False):
    dataset = load_wine()
    X_train, X_test, y_train, y_test = train_test_split(dataset.data, dataset.target, test_size=0.2, random_state=42)

    model = RandomForestClassifier(random_state=42) if use_random_forest else DecisionTreeClassifier(random_state=42)
    params = {
        'max_depth': [None, 2, 4, 6],
        'min_samples_split': [2, 5],
        'criterion': ['gini', 'entropy'] if not use_random_forest else ['gini']
    }

    print("\n--- Wine Dataset ---")
    print(f"Model: {'RandomForest' if use_random_forest else 'DecisionTree'}")
    best_model = train_and_evaluate_model(model, params, X_train, X_test, y_train, y_test, is_classification=True)
    visualize_top2_features(best_model, dataset.data, dataset.target, dataset.feature_names, dataset.target_names)


def run_diabetes_experiment(use_random_forest=False):
    dataset = load_diabetes()
    X_train, X_test, y_train, y_test = train_test_split(dataset.data, dataset.target, test_size=0.2, random_state=42)

    model = RandomForestRegressor(random_state=42) if use_random_forest else DecisionTreeRegressor(random_state=42)
    params = {
        'max_depth': [None, 2, 4, 6],
        'min_samples_split': [2, 5],
        'criterion': ['squared_error', 'absolute_error'] if not use_random_forest else ['squared_error']
    }

    print("\n--- Diabetes Dataset ---")
    print(f"Model: {'RandomForest' if use_random_forest else 'DecisionTree'}")
    best_model = train_and_evaluate_model(model, params, X_train, X_test, y_train, y_test, is_classification=False)
    visualize_top2_features(best_model, dataset.data, dataset.target, dataset.feature_names)


if __name__ == "__main__":
    run_wine_experiment(use_random_forest=False)
    run_wine_experiment(use_random_forest=True)
    run_diabetes_experiment(use_random_forest=False)
    run_diabetes_experiment(use_random_forest=True)
