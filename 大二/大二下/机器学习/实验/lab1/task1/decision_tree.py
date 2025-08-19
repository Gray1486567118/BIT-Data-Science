from sklearn.datasets import load_diabetes, load_wine
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeRegressor, DecisionTreeClassifier
from sklearn.metrics import accuracy_score, precision_score, recall_score
from sklearn.metrics import mean_squared_error, mean_absolute_error, median_absolute_error
from sklearn.model_selection import GridSearchCV
import matplotlib.pyplot as plt
import numpy as np


def wine():
    # Load dataset
    dataset = load_wine()

    # Split dataset
    X_train, X_test, y_train, y_test = train_test_split(dataset.data, dataset.target, test_size=0.2, random_state=42)

    # Create Decision Tree Classifier
    classifier = DecisionTreeClassifier(random_state=42)

    # Fit the model
    classifier.fit(X_train, y_train)

    # Make predictions
    y_pred = classifier.predict(X_test)

    # Evaluate the model
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted')
    recall = recall_score(y_test, y_pred, average='weighted')

    print("--- Wine Dataset ---")
    print(f"Decision Tree Classifier Accuracy: {accuracy:.6f}")
    print(f"Decision Tree Classifier Precision: {precision:.6f}")
    print(f"Decision Tree Classifier Recall: {recall:.6f}")


    # Define the parameter grid
    params = {
        'max_depth': [None, 2, 3, 4, 5, 10],
        'min_samples_split': [2, 5, 10],
        'criterion': ['gini', 'entropy']
    }

    # Perform grid search
    grid_search = GridSearchCV(classifier, params, cv=5, scoring='accuracy')
    grid_search.fit(X_train, y_train)
    
    # Make predictions
    y_pred = grid_search.predict(X_test)

    # Evaluate the model
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted')
    recall = recall_score(y_test, y_pred, average='weighted')

    print("\n--- Grid Search Results ---")
    print(f"Original parameters: criterion: {classifier.get_params()['criterion']}, "
          f"max_depth: {classifier.get_params()['max_depth']}, "
          f"min_samples_split: {classifier.get_params()['min_samples_split']}")
    print(f"Best parameters: {grid_search.best_params_}")
    print(f"Grid Search Decision Tree Classifier Accuracy: {accuracy:.6f}")
    print(f"Grid Search Decision Tree Classifier Precision: {precision:.6f}")
    print(f"Grid Search Decision Tree Classifier Recall: {recall:.6f}")

    # Plotting the decision tree
    importances = grid_search.best_estimator_.feature_importances_
    top2_indices = np.argsort(importances)[-2:]
    print("Top 2 feature names:", [dataset.feature_names[i] for i in top2_indices])

    X = dataset.data[:, top2_indices]
    y = dataset.target
    labels = dataset.target_names

    plt.figure(figsize=(8, 6))
    for label in np.unique(y):
        plt.scatter(X[y == label, 0], X[y == label, 1], label=labels[label], alpha=0.7)

    plt.xlabel(dataset.feature_names[top2_indices[0]])
    plt.ylabel(dataset.feature_names[top2_indices[1]])
    plt.legend()
    plt.title("Wine data (top 2 features)")
    plt.show()


def diabetes():
    dataset = load_diabetes()
    X_train, X_test, y_train, y_test = train_test_split(dataset.data, dataset.target, test_size=0.2, random_state=42)

    # Create Decision Tree Regressor
    regressor = DecisionTreeRegressor(random_state=42)
    regressor.fit(X_train, y_train)
    y_pred = regressor.predict(X_test)

    # Evaluate the model
    mse = mean_squared_error(y_test, y_pred)
    mae = mean_absolute_error(y_test, y_pred)
    medae = median_absolute_error(y_test, y_pred)
    print("\n\n--- Diabetes Dataset ---")
    print(f"Decision Tree Regressor Mean Squared Error: {mse:.2f}")
    print(f"Decision Tree Regressor Mean Absolute Error: {mae:.2f}")
    print(f"Decision Tree Regressor Median Absolute Error: {medae:.2f}")
    
    # Define the parameter grid
    params = {
        'max_depth': [None, 2, 3, 4, 5, 10],
        'min_samples_split': [2, 5, 10],
        'criterion': ['squared_error', 'friedman_mse', 'absolute_error']
    }

    # Perform grid search
    grid_search = GridSearchCV(regressor, params, cv=5, scoring='neg_mean_squared_error')
    grid_search.fit(X_train, y_train)
    y_pred = grid_search.predict(X_test)
    mse = mean_squared_error(y_test, y_pred)
    mae = mean_absolute_error(y_test, y_pred)
    medae = median_absolute_error(y_test, y_pred)
    print("\n--- Grid Search Results ---")

    print(f"Original parameters: criterion: {regressor.get_params()['criterion']}, "
      f"max_depth: {regressor.get_params()['max_depth']}, "
      f"min_samples_split: {regressor.get_params()['min_samples_split']}")

    print(f"Best parameters: {grid_search.best_params_}")
    print(f"Grid Search Decision Tree Regressor Mean Squared Error: {mse:.2f}")
    print(f"Grid Search Decision Tree Regressor Mean Absolute Error: {mae:.2f}")
    print(f"Grid Search Decision Tree Regressor Median Absolute Error: {medae:.2f}")

    # Plotting the decision tree
    importances = grid_search.best_estimator_.feature_importances_
    top2_indices = np.argsort(importances)[-2:]
    print("Top 2 feature names:", [dataset.feature_names[i] for i in top2_indices])

    X = dataset.data[:, top2_indices]
    y = dataset.target

    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(X[:, 0], X[:, 1], y, c=y, cmap='plasma')
    ax.set_xlabel(dataset.feature_names[top2_indices[0]])
    ax.set_ylabel(dataset.feature_names[top2_indices[1]])
    ax.set_zlabel('Disease Progression')
    plt.title("3D Scatter: Top 2 Features and Target")
    plt.show()



if __name__ == "__main__":
    wine()
    diabetes()