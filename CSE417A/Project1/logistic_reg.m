function [ w e_in iter ] = logistic_reg( X, Y, max_its )

% Author: Shane Deiley
% Date Completed: 10/2/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 3

%LOGISTIC_REG Learn logistic regression model using gradient descent
%   Inputs:
%       X : data matrix - in this case, cleveland-train.csv
%       Y : data labels (plus or minus 1)
%   Outputs:
%       w : weight vector
%       e_in : in-sample error (as defined in LFD)

% Initialize w as a column vector (said how it was done on piazza)
w = zeros(size(X,2) + 1, 1);

% Initialize other parameters
N = size(X,1);
eta = 10^(-1);

% Augment X with first column of ones
X = [ones(size(X,1),1) X];

% Algorithm for gradient descent - w should be done after
for i = 1:max_its
    
    % Compute the gradient g_t using matrix operations
    denom = (1 + exp(Y .* (X*w)));
    scaled_y = Y ./ denom;
    g_t = (-1/N) * (scaled_y)'*X;
    
    % Update the direction
    v_t = -(g_t);
    
    % Update the weight vector in that direction
    w = w + eta*(v_t');
    
    % Terminate if magnitude of each term in gradient is < 10^(-3)
    if( sum(abs(g_t) > 10^(-6)) < 1)
        iter = i;
        break;
    end
    
    iter = i;
end

% Now compute Ein using cross-entropy error
e_in = (1/N) * sum(log(1 + exp( -(Y .* (X*w)))));
  
end

