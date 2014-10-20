function [ overfit_m ] = computeOverfitMeasure( true_Q_f, N_train, N_test, var, num_expts )

% Author: Shane Deiley
% Date Completed: 10/14/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 4

%COMPUTEOVERFITMEASURE Compute how much worse H_10 is compared with H_2 in
%terms of test error. Negative number means it's better.
%   Inputs
%       true_Q_f: order of the true hypothesis
%       N_train: number of training examples
%       N_test: number of test examples
%       var: variance of the stochastic noise
%       num_expts: number of times to run the experiment
%   Output
%       overfit_m: vector of length num_expts, reporting each of the
%                  differences in error between H_10 and H_2

% Initialize overfit_m, the vector to hold all results for each experiment
overfit_m = zeros(num_expts,1);

% Loop through the experiment, recording result in overfit_m
for i = 1:num_expts
    
    % Generate the data sets with the target function f, degree true_Q_f
    [train, test] = generate_dataset(true_Q_f, N_train, N_test, sqrt(var));
    
    % == Now we need to generate hypothesis with weight vectors from these data sets ==

    % Get matrix of legendre polynomials of the training data
    legMat_train_d2 = computeLegPoly(train(:,1), 2);
    legMat_train_d10 = computeLegPoly(train(:,1), 10);
    legMat_test_d2 = computeLegPoly(test(:,1), 2);
    legMat_test_d10 = computeLegPoly(test(:,1), 10);
    
    % First, train using glmfit and the respective training sets
    w2 = glmfit(legMat_train_d2', train(:,2), 'normal', 'constant', 'off');
    w10 = glmfit(legMat_train_d10', train(:,2), 'normal', 'constant', 'off');

    % Make sure the w's are column vectors
    if (size(w2,2) ~= 1)
        w2 = w2';
    end
    if (size(w10,2) ~= 1)
        w10 = w10';
    end 

    % Weight each row termwise by w to get predictions for this test set
    pred2 = legMat_test_d2' * w2;
    pred10 = legMat_test_d10' * w10;

    % == To finish test error for H2 and H10, we need Eout for each as well ==

    % Now Eout with best fit hypothesis
    Eout_d2 = (1 ./ N_test) .* sum( (pred2 - test(:,2)) .^ 2);
    Eout_d10 = (1 ./ N_test) .* sum( (pred10 - test(:,2)) .^ 2);

    % Finally, the error difference for competing H2 and H10
    overfit_error = Eout_d10 - Eout_d2;
    
    % Record this iteration in overfit_m
    overfit_m(i) = overfit_error;
    
end % End the for loop

produce_plots(expt_data_mat_median, expt_data_mat_mean, var, Q_f, N);


end

