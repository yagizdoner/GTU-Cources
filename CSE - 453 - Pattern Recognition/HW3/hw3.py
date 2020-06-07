import pandas as pd  
import numpy as np  
from sklearn.model_selection import train_test_split, cross_val_score, GridSearchCV, KFold
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression

bankdata = pd.read_csv("bill_authentication.csv")  
X = bankdata.drop('Class', axis=1)  
y = bankdata['Class']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.20, random_state = 0)  

linearClassifier = SVC(kernel='linear')  
linearClassifier.fit(X_train, y_train)

print("\n -- LINEAR -- \n")
laccuracies = cross_val_score(estimator = linearClassifier, X = X_train, y = y_train, cv = 5)
print("Ortalama değer (mean): %",round(laccuracies.mean()*100,2))
print("std: %",round(laccuracies.std()*100))

print("\n -- POLYNOMIAL with Degree 8 -- \n")
poly8Classifier = SVC(kernel='poly', degree=8, gamma='auto')  
poly8Classifier.fit(X_train, y_train)

p8accuracies = cross_val_score(estimator = poly8Classifier, X = X_train, y = y_train, cv = 5)
print("Ortalama değer (mean): %",round(p8accuracies.mean()*100,2))
print("std: %",round(p8accuracies.std()*100))

print("\n -- POLYNOMIAL with Degree 35 -- \n")
poly35Classifier = SVC(kernel='poly', degree=35, gamma='auto')  
poly35Classifier.fit(X_train, y_train)

p35accuracies = cross_val_score(estimator = poly35Classifier, X = X_train, y = y_train, cv = 5)
print("Ortalama değer (mean): %",round(p35accuracies.mean()*100,2))
print("std: %",round(p35accuracies.std()*100))

print("\n -- GAUSSIAN -- \n")
GausClassifier = SVC(kernel='rbf', gamma='auto')  
GausClassifier.fit(X_train, y_train)

gaccuracies = cross_val_score(estimator = GausClassifier, X = X_train, y = y_train, cv = 5)
print("Ortalama değer (mean): %",round(gaccuracies.mean()*100,2))
print("std: %",round(gaccuracies.std()*100))

logistic = LogisticRegression()
penalty = ['l1','l2']
C = np.logspace(0,4,10)
hyperparameters = dict(C=C,penalty = penalty)
clf = GridSearchCV(logistic,hyperparameters,cv=5,verbose=0)
best_model = clf.fit(X_train,y_train)

kfold = KFold(n_splits=5,random_state=0)
model = LogisticRegression(C=best_model.best_estimator_.get_params()['C'],
							penalty = best_model.best_estimator_.get_params()['penalty'])

results = cross_val_score(model,X_train,y_train,cv=kfold)
print("Ortalama değer (mean): %",round(results.mean()*100,2))
print("Iyilesme Derecesi = %", (laccuracies-results).mean()*100)