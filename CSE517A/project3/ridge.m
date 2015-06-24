function [loss,gradient]=ridge(w,xTr,yTr,lambda)
% function w=ridge(xTr,yTr,lambda)
%
% INPUT:
% w weight vector (default w=0)
% xTr dxn matrix (each column is an input vector)
% yTr 1xn matrix (each entry is a label)
% lambda regression constant
%
% OUTPUTS:
% loss = the total loss obtained with w on xTr and yTr
% gradient = the gradient at w
%
[d,n]=size(xTr);

% Calculate loss function
loss = (yTr-w'*xTr)*(yTr-w'*xTr)'+lambda*(w'*w);
% gradient = 2*(xTr*(xTr'*w) + lambda*eye(d,d)*w) - 2*xTr*yTr'; %grad update rule
gradient = (2*(w'*xTr-yTr)*xTr')'+2*lambda*w; %grad update rule




