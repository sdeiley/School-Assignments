function [r,s]=hw3tests()
% function [r,s]=hw3tests()
%
% Tests the functions from homework assignment 1
% Please make sure that the error statements are instructive. 
%
% Output: 
% r=0 number of tests that broke
% s= statement describing the failed test (s={} if all succeed)
%


% Put in any seed below
rand('seed',31415926535);
% initial outputs
r=0;
s={};

% data set
N=50;
D=5;
x=[randn(D,N) randn(D,N)+2];
y=[ones(1,N) -ones(1,N)];

%% testing gradient of logistic
d=checkgrad('logistic',rand(D,1),1e-05,x,y);
if d>1e-10
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='Logistic function does not pass checkgrad.';
end;

%% logistic sanity check #1
if logistic(zeros(5,1),x(:,1),-1)-log(2)>eps,
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='Logistic function does not pass sanity check #1.';
end;

%% logistic sanity check #2
w=rand(5,1);
if w'*x+log(exp(logistic(w,x(:,1),1))-1)>eps,
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='Logistic function does not pass sanity check #2.';	
end;


% Computing the explicit leave-one-out error of OLS (Ordinary Least Squares)
err=zeros(1,length(y));
for i=1:length(y)
	x2=x;	
	y2=y;
	% remove ith data point
	x2(:,i)=[];	
	y2(i)=[];
	% do OLS and compute error of i^th example
	err(i)=(x(:,i)'*((x2*x2')\x2*y2')-y(i))^2;
end;
err=sqrt(mean(err));


try
	lerr=looreg(x,y);
catch
	lerr=99999999;
end;
if abs(err-lerr)>1e-10
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='looreg.m is wrong. Error does not match leave-one-out OLS error.';
end;

%% checking gradient descent
f=@(w) squaredloss(w,x,y);
w=grdescent(f,rand(5,1),1e-05,1000,1e-09);
[loss,gr]=f(w);
if norm(gr)>1e-05,
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='Gradient descent seems wrong - gradient is not zero at minimum!';
end;	

function [loss,gradient]=squaredloss(w,x,y);
%function [loss,gradient]=squaredloss(w,x,y);

[d,n]=size(x);
diff=(w'*x-y);
gradient=2.*x*diff'./n;
loss=mean(diff.^2);


