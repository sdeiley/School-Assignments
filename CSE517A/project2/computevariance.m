function variance=computevariance(xTe,treedepth,hbar)
% function variance=computevariance(xTe,OFFSET,treedepth,Nsmall,NMODELS,hbar)
% 
% computes the variance of classifiers trained on data sets from
% toydata.m with pre-specified "OFFSET" and a finite "treepdeth",
% evaluated on xTe. 
% the prediction of the average classifier is assumed to be stored in "hbar".
%
% The "infinite" number of models is estimated as an average over NMODELS. 
%
% INPUT:
% xTe       | dxn matrix, of n column-wise input vectors (each d-dimensional)
% treedepth | max treedepth of the decision tree models
% hbar      | 1xn vector of the predictions of hbar on the inputs xTe
% 

global Nsmall NMODELS OFFSET;
[~,n]=size(xTe);
variance=zeros(1,n);
for j=1:NMODELS
    % Get new training dataset and create tree
    [xTr,yTr]=toydata(OFFSET,Nsmall);
    T = id3tree(xTr,yTr,treedepth);
    % Calculate variance using hbar and add to previous variance
    variance = variance + (evaltree(T,xTe)-hbar).^2;
end;
% Get mean variance across all points and divide by number of models
%variance=mean(variance)/NMODELS;
variance = mean(variance)./NMODELS;


