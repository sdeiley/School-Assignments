% Author: Shane Deiley (and Mark Heimann)
% January 29th, 2014

function G=innerproduct(x1,x2)
% function G=innerproduct(x1,x2)
%	
% Computes the inner-product matrix. 
% Syntax:
% D=innerproduct(x1,x2)
% Input:
% x1: dxn data matrix with n vectors (columns) of dimensionality d
% x2: dxm data matrix with m vectors (columns) of dimensionality d
%
% Output:
% Matrix G of size nxm 
% G(i,j) is the inner-product between vectors x1(:,i) and x2(:,j)
%
% call with only one input:
% innerproduct(x1)=innerproduct(x1,x1)
%


if (nargin==1) % case when there is only one input (x1)
	G = x1' * x1;
    return;

else  % case when there are two inputs (x1,x2)
	G = x1' * x2;
    return;

end;




