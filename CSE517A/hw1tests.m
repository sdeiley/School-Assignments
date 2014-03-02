% Author: Shane Deiley (and Mark Heimann)
% January 29th, 2014

%We authored only the code below line 43

function [r,s]=hw1tests()
% function [r,s]=hw1tests()
%
% Tests the functions from homework assignment 1
% Please make sure that the error statements are instructive. 
%
% Output: 
% r=0 number of tests that broke
% s= statement describing the failed test (s={} if all succeed)
%


% Put in any seed below
rand('seed',31415926535);
% initial outputs
r=0;
s={};

% Example:
% A simple test is to look if the diagonal is all zero
x=rand(10,100); % define some random test points
d= diag(l2distance(x));	% extract diagonal of distance matrix
if ~all(d<eps*100)			% if test failed ...
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='Distance from a vector to itself is not zero.';
end;

x=[[1,0];[0,1]];
z=[[0,0];[1,1]];
D=l2distance(x,z);
D2=[[sqrt(2),sqrt(2)];[0,0]];
if ~(max(max(abs(D2-D)))<100*eps)
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='Distances between xor vectors are not correct.';
end;


%% Define your own tests here:

% Innerproduct test
% Just tests the expected result of two matrix calculations

A = [1 2; 3 4];
B = [2 3; 2 3];
C = innerproduct(A,B);
D = innerproduct(A);

expIPofAandB = [8 12
                12 18];

expIPofAtA = [10 14
               14 20];

if ~isequal(expIPofAandB, C)
    r=r+1;
    s{length(s)+1}='Innerproduct failed for two matrices';
end;

if ~isequal(expIPofAtA, D)
    r=r+1;
    s{length(s)+1}='Innerproduct failed for one matrix';
end;


% l2distance test
% Just tests that the diagonals are zero for one matrix case

dist = [ 4 5 6; 8 2 3; 5 8 3];
DistMatrix = l2distance(dist);
diagonal = diag(DistMatrix);
testZeros = [0; 0; 0];

if ~isequal(diagonal, testZeros)
    r = r+1;
    s{length(s) + 1} = 'One matrix l2distance test failed';
end;


% findknn Test
% Test a simple case to check two vectors are in fact the closest

% First test that if given a distance matrix, it correctly
% finds the dists and indices matrices
testDist = [ 2 3 2; 5 4 6; 1 1 1];
expDists = [1 1 1; 2 3 2; 5 4 6];
expIndices = [3 3 3; 1 1 1; 2 2 2];
[testDists, testIndices] = sort(testDist, 1);
if ~isequal(expDists, testDists)
    r = r+1;
    s{length(s)+1}='The smallest distance for a given x(i) was incorrectly found given a distance matrix';
end;
if ~isequal(expIndices, testIndices)
    r = r+ 1;
    s{length(s)+1}='The indices matrix did not correctly return the right positions'
end;

% Now just check a simple case where the zero vectors should be closest
X = [0 1; 0 2];
Z = [3 0; 1 0];

[indices,dists] = findknn(X,Z,1);

shortestDistance = dists(2);
correctIndex = indices(2);

if ~isequal(shortestDistance,0)
    r =r+1;
    s{length(s)+1}='Did not identify zero vectors distance as 0';
end;
if ~isequal(correctIndex, 1)
    r=r+1;
    s{length(s)+1}='Did not identify zero vectors as nearest neighbors (indices error)';
end;

% analyze test
% test simple case

a = [1 5 2 4 6];
b = [5 2 6 4 3];
number = analyze('acc',a,b);

if ~(abs(number - .2) < 100*eps)
    r=r+1;
    s{length(s)+1}='Analyze did not find the correct proportion for case acc';
end;


% knn Classifier test

train_set = [1,0.9; 1,1; 1, 0.7; 0.9, 0.9; -0.9, -0.9; -1, -1]';
train_label = [1,1,1,1,2,2];
test_set = [0.5,0.5;-0.6,-0.9]';
test_label = [1,2];
predict_label = knnclassifier(train_set, train_label, test_set,1);
if(max(abs(test_label - predict_label)) > 100*eps)
    r = r + 1;
    s{length(s) + 1} = 'KNN-classification failed.';
end
