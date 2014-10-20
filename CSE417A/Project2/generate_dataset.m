function [ train_set, test_set ] = generate_dataset( Q_f, N_train, N_test, sigma )

% Author: Shane Deiley
% Date Completed: 10/14/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 4

%GENERATE_DATASET Generate training and test sets for the Legendre
%polynomials example
%   Inputs:
%       Q_f: order of the hypothesis
%       N_train: number of training examples
%       N_test: number of test examples
%       sigma: standard deviation of the stochastic noise
%   Outputs:
%       train_set and test_set are both 2-column matrices in which each row
%       represents an (x,y) pair

% Need to compute two 'N' by '2' matrices with (x,y) pairs according to the
% formula: y_n = f(x_n) + sigma*epison_n where:
%   f(x_n) is the sum of the legendra polynomials from 0 to Q_f of x_n
%   epison_n is an i.i.d. standard normal random variate

% Initialize sets
train_set = zeros(N_train, 2);
test_set = zeros(N_test, 2);

% Generate x vector, where x is pulled from unifrom distribution [-1,1]
train_set(:,1) = (2) .* rand(N_train, 1) - 1;
test_set(:,1) = (2) .* rand(N_test, 1) - 1;

% Generate epison vector, where epison_n is pulled from the standard normal
% distribution. For convenience, I scale by sigma here instead of when
% calculating y values.
epsilon_train = sigma .* randn(N_train,1);
epsilon_test = sigma .* randn(N_test,1);

% === Compute values for y_n for each generated x_n ===

% First, get the legendre matrices with x_n inputs
z_train = computeLegPoly(train_set(:,1),Q_f);
z_test = computeLegPoly(test_set(:,1), Q_f);

% Generate 1 a vector so that f is the same for train and test
randomAs = randn(Q_f+1,1);

% Get the term to scale the a terms by
q_vec = 0:Q_f;
q_vec = 1 ./ (2 .* q_vec + 1);
scale_term = sqrt(sum(q_vec));

% Scale the a's
randomAs = randomAs ./ scale_term;

% Now multiply the transform z matrices by the weights
z_train = randomAs' * z_train;
z_test = randomAs' * z_test;

% Each entry y_n is the sum of a column of z, so take the transpose of the
% sum of columns vector and add the weighted stochastic noise vector
% epision
train_set(:,2) = (sum(z_train, 1))' + epsilon_train;
test_set(:,2) = (sum(z_test, 1))' + epsilon_test;

% Now test_set and train_set are done

end

