% Author: Shane Deiley (and Mark Heimann)
% January 29th, 2014

function [indices,dists]=findknn(xTr,xTe,k);
% function [indices,dists]=findknn(xTr,xTe,k);
%
% Finds the k nearest neighbors of xTe in xTr.
%
% Input:
% xTr = dxn input matrix with n column-vectors of dimensionality d
% xTe = dxm input matrix with m column-vectors of dimensionality d
% k = number of nearest neighbors to be found
% 
% Output:
% indices = kxm matrix of the where indices(i,j) is the i^th nn of xTe(:,j)
% dists = Euclidean distances to the respective nearest neighbors
%

n = size(xTr, 2);
m = size(xTe, 2);

distMatrix = l2distance(xTr, xTe);

% Note: sort function in reverse order to findknn
[distInitial, indicesInitial] = sort(distMatrix, 1);

dists = distInitial(1:k, 1:m);
indices = indicesInitial(1:k, 1:m);
