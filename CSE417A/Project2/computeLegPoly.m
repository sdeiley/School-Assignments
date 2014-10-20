function [ z ] = computeLegPoly( x, Q )

% Author: Shane Deiley
% Date Completed: 10/14/14
% Class: CSE417A - Introduction to Machine Learning
% Assignment: Project 4

%COMPUTELEGPOLY Return the Qth order Legendre polynomial of x
%   Inputs:
%       x: vector (or scalar) of reals in [-1, 1]
%       Q: order of the Legendre polynomial to compute
%   Output:
%       z: matrix where each column is the Legendre polynomials of order 0 
%          to Q, evaluated atthe corresponding x value in the input

% Make sure x is a row vector
if (size(x,1) ~= 1)
    x = x';
end

% Initialize the array of the output
% z is 'Q + 1' by 'x' where each column n is the values for
% each of the legendre polynomials (0 to Q) for x_n
z = zeros(Q + 1, size(x,2));

% Define the constant values, L_0(x) and L_1(x)
z(1,:) = 1;
z(2,:) = x;

% Calculate each row by the recursive definition for legendre polynomials
% with q > 2
for i = 3:(Q+1)
    % Recursive algorithm:
        % Li(x) = (2i-1)/i * x * Li-1(x) - (i-1)/i * Li-2(x)
    % Compute this for a whole row with element wise multiplication
    k = i - 1; % Legendre polynomials start at 0, not 1 like matlab indices
    z(i,:) = ((2*k - 1)/k) * x .* z(i-1,:) - (((k - 1)/k) .* z(i-2,:));
end


end

