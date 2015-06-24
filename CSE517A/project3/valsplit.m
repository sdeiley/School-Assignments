%% Split data 
[d,n]=size(X);
itr=1:ceil(0.8*n);
ite=ceil(0.8*n)+1:n;
xTr=X(:,itr);
yTr=Y(itr);
xTv=X(:,ite);
yTv=Y(ite);
clear('itr','ite','n','d');