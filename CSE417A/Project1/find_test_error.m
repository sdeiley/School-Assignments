function [ test_error ] = find_test_error( w, X, y )

% Author: Shane Deiley
% Date Completed: 10/2/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 3

%FIND_TEST_ERROR Find the test error of a linear separator
%   This function takes as inputs the weight vector representing a linear
%   separator (w), the test examples in matrix form with each row
%   representing an example (X which in this case, is found in cleveland-test.csv),
%   and the labels for the test data as a column vector (y).
%   The labels are assumed to be plus or minus one. The
%   function returns the error on the test examples as a fraction. The
%   hypothesis is assumed to be of the form (sign ( [1 x(n,:)] * w )

% Augment X again so dimensions agree
X = [ones(size(X,1),1) X];

% First calculate hypothesis vector
h = sign( X * w);

% Now calculate the proprotion of correct classifications
test_error = sum( (h-y)~=0 )/ size(h,1);

end

