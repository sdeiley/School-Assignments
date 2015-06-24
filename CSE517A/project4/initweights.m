function W=initweights(wst);
% function W=initweights(wst);
% 
% returns a randomly initialized weight vector for a given neural network
% architecture.

entry=cumsum(wst(1:end-1).*wst(2:end)+wst(1:end-1)); % entry points into weights
W=randn(entry(end),1)./10;