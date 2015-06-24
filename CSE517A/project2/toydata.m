function [x,y]=toydata(OFFSET,N)
% function [x,y]=toydata(OFFSET,N)
% 
% This function constructs a binary data set. 
% Each class is distributed by a standard Gaussian distribution.
% INPUT: 
% OFFSET:  Class 1 has mean 0,  Class 2 has mean 0+OFFSET (in each dimension). 
% N: The function returns N data boints ceil(N/2) are of class 2, the rest
% of class 1
%
%

x=randn(2,N);
x(:,ceil(N/2):end)=x(:,ceil(N/2):end)+OFFSET;
y=ones(1,N);
y(ceil(N/2):end)=y(ceil(N/2):end).*2;
jj=randperm(N);
x=x(:,jj);
y=y(jj);

