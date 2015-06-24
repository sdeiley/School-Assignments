function testfunc=hw2contest(xTr,yTr)
%% Modify code below here
% do training
T=id3tree(xTr,yTr);

% define the testing function
testfunc=@(xTe,yTe) evaltree(T,xTe);

% You can evaluate your code with some validation data xTv,yTv
% calling:
% valerror=testfunc(xTv,yTv);
%