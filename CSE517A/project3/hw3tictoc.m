function auc=hw3tictoc;

clear all;
loaddata('data_train','data_train')
load data_train
trainspamfilter(X,Y); % classifier saved as w0.mat

% clear all;
% loaddata('data_test','data_test')
% load data_test
[fpr,tpr,auc]=spamfilter(X,Y);



