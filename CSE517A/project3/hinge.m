function [loss,gradient]=hinge(w,xTr,yTr,lambda)
% function w=ridge(xTr,yTr,lambda)
%function [loss,gradient,preds]=hinge(w,xTr,yTr,lambda)
% INPUT:
% xTr dxn matrix (each column is an input vector)
% yTr 1xn matrix (each entry is a label)
% lambda regression constant
% w weight vector (default w=0)
%
% OUTPUTS:
%
% loss = the total loss obtained with w on xTr and yTr
% gradient = the gradient at w
%

[d,n]=size(xTr);

loss = sum(1-yTr.*(w'*xTr));
loss = max(loss,0);
% if loss == 0
%     gradient = 2*lambda*w;
% else
%     gradient = -2*(1-yTr*(xTr'*w))*(yTr*xTr')' + 2*lambda*w;
% end
y1 = yTr; x1 = xTr; % setting negative values to zero
y1(yTr.*(w'*xTr)>1) = 0;
x1(:,yTr.*(w'*xTr)>1) = 0;
grad = -x1*y1';
gradient = sum(grad,2) + 2*lambda*w;

% loss = loss^2 + lambda*w'*w;
loss = loss + lambda*w'*w;


