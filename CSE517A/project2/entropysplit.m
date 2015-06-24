function [feature,cut,Hbest]=entropysplit(xTr,yTr,weights)
% function [feature,cut,Hbest]=entropysplit(xTr,yTr,weights);
% 
% Finds the best (feature,cutoff) pair to split data, minimizing entropy.
% 
% INPUT:
% xTr | dxn matrix of n column vectors with d dimensions
% yTr | 1xn row vector of labels
% weights : 1xn vector of where weight(i) is the weight of example i
%
% OUTPUT:
% feature | best feature to split
% cut     | Value to split on.
% Hbest   | Loss of best split
% 
[d,n]=size(xTr);
if nargin<3,
    weights=ones(1,n)./n;
end;
weights=weights./sum(weights); % Weights need to sum to one
%K=length(unique(yTr));
%K=max(yTr);
[~,un,yTr]=unique(yTr);
K=length(un);

feature=0;
cut=0;
Hbest=Inf;
for i=1:d
	[sx,ii]=sort(xTr(i,:));
	y=yTr(ii);
	ws=weights(ii);
        
	Y=zeros(n,K);
	% The following line is equivalent to this loop:
	for j=1:n
	    Y(j,y(j))=ws(j);
	end;
% 	Y(sub2ind(size(Y),1:n,y))=ws;
            
	P=bsxfun(@times,cumsum(Y),1./cumsum(ws'));               
	Q=-P.*log2(P);Q(isnan(Q))=0;				
	Q=bsxfun(@times,Q,cumsum(ws'));       
        
	P2=bsxfun(@times,cumsum(Y(end:-1:1,:)),1./cumsum(ws(end:-1:1)'));
        
	Q2=-P2.*log2(P2);
	Q2(isnan(Q2))=0;
	Q2=bsxfun(@times,Q2,cumsum(ws(end:-1:1)'));
	Q2=Q2(end-1:-1:1,:);

	idif=find(abs(diff(sx))>eps*100); % find places where the features differ
	H=sum(Q(idif,:)+Q2(idif,:),2);
	if isempty(H),continue;end;
	[hb,jc]=min(H); % impurity reduction at best split

	if hb<Hbest,  % New best split found
		cut=mean([sx(idif(jc)) sx(idif(jc)+1)]); % cut <=T.cut		    
		feature=i;
		Hbest=hb;
	end;
end;
