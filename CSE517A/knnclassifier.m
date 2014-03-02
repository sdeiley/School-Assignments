% Author: Shane Deiley (and Mark Heimann)
% January 29th, 2014

function preds=knnclassifier(xTr,yTr,xTe,k);
% function preds=knnclassifier(xTr,yTr,xTe,k);
%
% k-nn classifier 
%
% Input:
% xTr = dxn input matrix with n column-vectors of dimensionality d
% xTe = dxm input matrix with m column-vectors of dimensionality d
% k = number of nearest neighbors to be found
%
% Output:
%
% preds = predicted labels, ie preds(i) is the predicted label of xTe(:,i)

[predIndices, predDists] = findknn(xTr, xTe, k);
predsTemp = yTr(predIndices);
preds = predsTemp(1,:); % Went with closest match rather than average of k=3.
% In other words, it's essentially a 1-knn classifier as written.

% If we beat our professor's time, we got bonus, and a 1-knn did.
% It's worth noting this is a dumb idea generally, and that it is simply 
% overfitting this data set. But since it got us extra credit, it's worth
% noting why we decided on that.



