% Author: Shane Deiley (and Mark Heimann)
% January 29th, 2014

function D=l2distance(x1,x2)
% function D=l2distance(x1,x2)
%	
% Computes the Euclidean distance matrix. 
% Syntax:
% D=l2distance(x1,x2)
% Input:
% x1: dxn data matrix with n vectors (columns) of dimensionality d
% x2: dxm data matrix with m vectors (columns) of dimensionality d
%
% Output:
% Matrix D of size nxm 
% D(i,j) is the Euclidean distance of x1(:,i) and x2(:,j)
%
% call with only one input:
% l2distance(x1)=l2distance(x1,x1)
%


if (nargin==1) % case when there is only one input (x1)
    n = size(x1, 2);
	G = innerproduct(x1);
    A = ones(1, n);
    
    % Only need diagonal for sum, for Sx is a matrix such that
    % each column
    sVect = diag(G);
    Sx = sVect * A;
    
    % This gives the squared Euclid. dist. matrix.
    Dtemp1 = Sx + Sx' -2 * G;
    D = sqrt(Dtemp1);
    return;

else  % case when there are two inputs (x1,x2)
    
    % define dimensions
    n = size(x1, 2);
    m = size(x2, 2);
    
    % one dimensional G's
    G = innerproduct (x1);
    G2 = innerproduct (x2);
    
    % This is the column for Sx (all columns the same)
    sxVect = diag(G);
    
    % Constructing Sx
    A = ones(1,m);
    Sx = sxVect * A;
    
    % This is the row for Sz (all rows the same)
    szVect = diag(G2);
    
    % Constructing Sz
    B = ones(n,1);
    Sz = B * szVect';
    
    % Add to find D^2
	Dtemp = (-2 * innerproduct(x1, x2)) + Sx + Sz;
    D = sqrt(Dtemp);
end;
%



