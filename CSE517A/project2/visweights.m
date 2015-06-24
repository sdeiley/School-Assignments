function visweights
% function visweights
% 
% Constructs an artificial version of iris, to see the cut of weighted features.
%

clear all;

load('iris');
ii=find(yTr>1);
xTr=xTr(1:2,ii);
yTr=yTr(ii);

xTr(1,1)=xTr(1,6);

weights=ones(1,length(yTr));
weights(1)=100;
weights(6)=100;
weights=weights./sum(weights);

clf
s=scatter(xTr(1,:),xTr(2,:),weights.*10000,yTr,'Marker','.');

T=id3tree(xTr,yTr,2,weights);
vistree(T);