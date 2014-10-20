% Author: Shane Deiley
% Date Completed: 10/2/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 3

% A script written to test the other other functions

% Read in Train and format correctly
train_set = csvread('./cleveland-train.csv', 1, 0);
train_X = train_set(:,1:13);
train_Y = (train_set(:,14) * 2) - 1;

% Read in Test and format correctly
test_set = csvread('./cleveland-test.csv', 1, 0);
test_X = test_set(:,1:13);
test_Y = (test_set(:,14) * 2) - 1;

% 10 thousand iterations
[w_10k, e_in_10k] = logistic_reg(train_X, train_Y, 10000);
test_err_ten_thousand = find_test_error(w_10k, test_X, test_Y);
disp(['test_err_ten_thousand = ', num2str(test_err_ten_thousand)])

% 100 thousand iterations
[w_100k, e_in_100k] = logistic_reg(train_X, train_Y, 100000);
test_error_one_hundred_thousand = find_test_error(w_100k, test_X, test_Y);
disp(['test_err_one_hundred_thousand = ', num2str(test_error_one_hundred_thousand)])

% 1 million iterations
[w_1m, e_in_1m] = logistic_reg(train_X, train_Y, 1000000);
test_error_one_million = find_test_error(w_1m, test_X, test_Y);
disp(['test_err_one_million = ', num2str(test_error_one_million)])
