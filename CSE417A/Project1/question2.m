% Author: Shane Deiley
% Date Completed: 10/2/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 3

% Question 3.2: 
% Download the handwritten digits dataset from http://amlbook.com/support.
% html and familiarize yourself with the data. The matlab code for plotting images is also a
% useful tool to get acquainted with. Now, we will be working on the problem of deciding
% whether or not an image is a “1”, using both the raw data (zip.train and zip.test)
% and another version of the dataset that extracts only two features, symmetry and intensity
% (features.train and features.test). Write a matlab script (which you will submit
% along with your code for Question 1) called question2.m that does the following:

% - Loads the data in zip.train and trains a logistic regression model using matlab’s
% glmfit function for predicting the probability that an image is a “1” or not on that
% data.

% - Applies the model to classify the data (using a probability of 0.5 as
% the threshold) in both zip.train and zip.test (for the same probelm of
% classifying whether an image is a "1" or not) and reports the
% classification error on both the training and test data.

% - Repeats the above two steps for features.train and features.test

% ===== BEGIN SOLUTION =====

% Load the data
x_train = load('zip.train');
x_test = load('zip.test');

% Take the first column as y (the handwritten digit id's)
y_train = x_train(:,1);
x_train = x_train(:,2:257);
y_test = x_test(:,1);
x_test = x_test(:,2:257);

% Relabel why based on its id being 1 or not
y_train = ((y_train-1)== 0);
y_test = ((y_test-1)==0);


% Now train a model to predict the probability of a digit being a '1'
w = glmfit(x_train, y_train, 'binomial');

% Append ones to data matrices for dimensional consistency
x_train = [ones(size(x_train,1),1) x_train];
x_test = [ones(size(x_test,1),1) x_test];

% Reformat y's for accurate error difference
y_train = y_train *2 - 1;
y_test = y_test * 2 - 1;

% Classify the error on the train data
h_train = sign(x_train * w);
train_error_zip = sum( (h_train-y_train) ~= 0 )/size(h_train,1)

% Classify the error on the test data
h_test = sign(x_test * w);
test_error_zip = sum( (h_test-y_test) ~= 0)/size(h_test,1)

% Now the same process for the features ones
xtrain = load('features.train');
xtest = load('features.test');

% First column
ytrain = xtrain(:,1);
xtrain = xtrain(:,2:3);
ytest = xtest(:,1);
xtest = xtest(:,2:3);

% Relabel why based on its id being 1 or not
ytrain = ((ytrain-1)== 0);
ytest = ((ytest-1)==0);

% Now train a model to predict the probability of a digit being a '1'
w2 = glmfit(xtrain, ytrain, 'binomial');

% Append ones to data matrices for dimensional consistency
xtrain = [ones(size(xtrain,1),1) xtrain];
xtest = [ones(size(xtest,1),1) xtest];

% Reformat y's for accurate error difference
ytrain = ytrain*2-1;
ytest = ytest*2-1;

% Classify the error on the train data
htrain = sign(xtrain * w2);
train_error_features = sum( (htrain-ytrain) ~= 0 )/size(htrain,1)

% Classify the error on the test data
htest = sign(xtest * w2);
test_error_features = sum( (htest-ytest) ~= 0)/size(htest,1)

