function [loss,gradient]=logistic(w,xTr,yTr,lambda)
% function w=logistic(w,xTr,yTr)
%
% INPUT:
% xTr dxn matrix (each column is an input vector)
% yTr 1xn matrix (each entry is a label)
% w weight vector (default w=0)
%
% OUTPUTS:
% 
% loss = the total loss obtained with w on xTr and yTr
% gradient = the gradient at w
%

[d,n]=size(xTr);

loss = 0;
for i = 1:n
    loss = loss + log(1 + exp(-yTr(i)*w'*xTr(:,i)));
end
%loss = loss/n;
%loss2 = log(1 + exp(-w'*xTr*yTr'));
%disp([loss loss2]);

gradient = zeros(d,1);
for i = 1:n
    gradient = gradient - (yTr(i)*xTr(:,i))./(1+exp(yTr(i)*w'*xTr(:,i)));
end
%gradient=gradient./n;
%gradient2 = -1.*(xTr*yTr')./(1 + exp(w'*xTr*yTr'));
%disp(gradient);disp(gradient2);

%loss = log(1 + exp(-w'*xTr*yTr'));
%gradient = -1.*(xTr*yTr')./(1 + exp(w'*xTr*yTr'));


%gradient = -1.*(xTr*yTr'*exp(-w'*xTr*yTr')) ./(1 + exp(-w'*xTr*yTr'));
% gradnum = exp(-w'*xTr*yTr')*(-xTr*yTr');
% graddenom = 1./(1+exp(-w'*xTr*yTr'));
% gradient = gradnum.*graddenom;
