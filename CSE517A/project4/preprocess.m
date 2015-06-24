function [xTr,xTe,u,m]=preprocess(xTr,xTe);
% function [xTr,xTe,u,m]=preprocess(xTr,xTe);
%
% Preproces the data to make the training features have zero-mean and
% standard-deviation 1
%
% output:
% xTr - pre-processed training data 
% xTe - pre-processed testing data
% 
% u,m - any other data should be pre-processed by x-> u*(x-m)
%

[d,n] = size(xTr);

m = mean(xTr,2);
xTr = xTr-m(:,ones(1,n));
xTe = xTe-m(:,ones(1,size(xTe,2)));

u = 1./max(abs(xTr),[],2);

u = diag(u);
xTr = u*xTr;
xTe = u*xTe;
    