function [w]=grdescent(func,w0,stepsize,maxiter,tolerance)
% function [w]=grdescent(func,w0,stepsize,maxiter,tolerance)
%
% INPUT:
% func function to minimize
% w0 = initial weight vector 
% stepsize = initial gradient descent stepsize 
% tolerance = if norm(gradient)<tolerance, it quits
%
% OUTPUTS:
% 
% w = final weight vector
%

if nargin<5,tolerance=1e-02;end;

% Assuming that func is an inline function

e = inf; %initialize error
prevLoss = inf;
w = w0; wprev = w0; %initialize weights and stored weights
prevLoss2 = inf;
n = 1; %iteration counter
while (e > tolerance) && (n < maxiter)
%     disp('Iteration: ');disp(n);
    [loss, gradient] = func(w);
%     disp('Loss: '); disp(loss);
    if loss <= prevLoss
        wprev = w; %save previous weight
        prevLoss2 = prevLoss;
        prevLoss = loss;
        w = w - stepsize.*gradient; %update weight
        stepsize = 1.01*stepsize; %increase stepsize
        e = norm(gradient); %compute error
        n = n+1;
%         disp(n);
    else
%         disp('Loss less...');
        w = wprev;
        prevLoss = prevLoss2;
        stepsize = 0.5*stepsize;
    end
end
%disp('n = ');disp(n);
