function [plot_result] = produce_plots(expt_data_mat_median, expt_data_mat_mean, var, Q_f, N)

% Author: Shane Deiley
% Date Completed: 10/14/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 4

% This is a plotting script made for showing results for various
% experiments of our overfit computations.

plot_result = 0;
% First hold N = 120 to see how the stochastic noise effects our
% results
figure('Name','Varying Var Median','NumberTitle', 'off')
plot(var, squeeze(expt_data_mat_median(1,3,:)), var, squeeze(expt_data_mat_median(2,3,:)), var, squeeze(expt_data_mat_median(3,3,:)), var, squeeze(expt_data_mat_median(4,3,:)));
title('Graph of Median Error with varying Stochastic Noise, Holding N = 120')
xlabel('Variance = [0,0.5,1,1.5,2]')
ylabel('Median Error for a given var after 500 Trials')
legend('Q_f = 5', 'Q_f = 10', 'Q_f = 15', 'Q_f = 20', 'location', 'northwest')


% Same thing with mean
figure('Name','Varying Var Mean','NumberTitle', 'off')
plot(var, squeeze(expt_data_mat_mean(1,3,:)), var, squeeze(expt_data_mat_mean(2,3,:)), var, squeeze(expt_data_mat_mean(3,3,:)), var, squeeze(expt_data_mat_mean(4,3,:)));
title('Graph of Mean Error with varying Stochastic Noise, Holding N = 120')
xlabel('Variance = [0,0.5,1,1.5,2]')
ylabel('Mean Error for a given var after 500 Trials')
legend('Q_f = 5', 'Q_f = 10', 'Q_f = 15', 'Q_f = 20', 'location', 'northwest')

% Now hold var = 2 to see how the degree of the target function
% affects our error
figure('Name','Varying Q_f Median','NumberTitle', 'off')
plot(Q_f, squeeze(expt_data_mat_median(:,2,5)), Q_f, squeeze(expt_data_mat_median(:,3,5)));
title('Graph of Median Error with varying Target Function Degree Q_f, Holding var = 2')
xlabel('Q_f = [5, 10, 15, 20]')
ylabel('Median Error for a given Q_f after 500 Trials')
legend('N = 80', 'N = 120', 'location', 'northeast')


% Same thing with mean
figure('Name','Varying Q_f Mean','NumberTitle', 'off')
plot(Q_f, squeeze(expt_data_mat_mean(:,2,5)), Q_f, squeeze(expt_data_mat_mean(:,3,5)));
title('Graph of Mean Error with varying Target Function Degree Q_f, Holding var = 2')
xlabel('Q_f = [5, 10, 15, 20]')
ylabel('Mean Error for a given Q_f after 500 Trials')
legend('N = 80', 'N = 120', 'location', 'northeast')

% Now hold Q_f = 10 to see how the degree of the target function
% affects our error
figure('Name','Varying N Median','NumberTitle', 'off')
plot(N, squeeze(expt_data_mat_median(2,:,1)), N, squeeze(expt_data_mat_median(2,:,2)), N, squeeze(expt_data_mat_median(2,:,3)), N, squeeze(expt_data_mat_median(2,:,4)), N, squeeze(expt_data_mat_median(2,:,5)));
title('Graph of Median Error with varying Input Size N, Holding Q_f = 10')
xlabel('N = [40, 80, 120]')
ylabel('Median Error for a given N after 500 Trials')
legend('var = 0', 'var = 0.5', 'var = 1', 'var = 1.5', 'var = 2', 'location', 'northeast')


% Same thing with mean
figure('Name','Varying N Mean','NumberTitle', 'off')
plot(N, squeeze(expt_data_mat_mean(2,:,1)), N, squeeze(expt_data_mat_mean(2,:,2)), N, squeeze(expt_data_mat_mean(2,:,3)), N, squeeze(expt_data_mat_mean(2,:,4)), N, squeeze(expt_data_mat_mean(2,:,5)));
title('Graph of Mean Error with varying Input Size N, Holding Q_f = 10')
xlabel('N = [40, 80, 120]')
ylabel('Mean Error for a given N after 500 Trials')
legend('var = 0', 'var = 0.5', 'var = 1', 'var = 1.5', 'var = 2', 'location', 'northeast')

plot_result = 1;