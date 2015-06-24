function BDT=boosttree(x,y,nt,maxdepth)
% function BDT=boosttree(x,y,nt,maxdepth)
%
% Learns a boosted decision tree on data x with labels y.
% It performs at most nt boosting iterations. Each decision tree has maximum depth "maxdepth".
%
% INPUT: 
% x  | input vectors dxn
% y  | input labels 1xn
% nt | number of trees (default = 100)
% maxdepth | depth of each tree (default = 3)
%
% OUTPUT:
% BDT | Boosted DTree
%


%% fill in code here
if nargin < 4
    maxdepth = 3;
end

if nargin < 3
    nt = 100;
end

[d,n] = size(x);

% Initialize variables
weights = ones(1,n)./n;
BDTemp = cell(1,nt);
tree = id3tree(x,y,maxdepth,weights); 
BDTemp{1}=tree;

for i = 2:1:nt
    % Calculate weak learner
     
    BDTemp{i} = id3tree(x,y,maxdepth,weights);
    
    % Get predictions of learner
    h = evaltree(BDTemp{i},x);
    h = (h-1.5).*2;
    y = (y-1.5).*2;
    
    % Calculate error
    error = sum(weights(y~=h));
    
    % Break if error is really bad
    if error > .5
        break;
    end
    
    % Get learning reate
    alpha = .5*log((1-error)/error);
    
    % Calculate new weights
    weights = weights.*exp(-alpha.*h.*y)./(2*sqrt(error*(1-error)));
    
    % Need old y for tree train
    y = .5.*y + 1.5;
end

% Count how many non-null elements are in cell array
BDT = cell(1,i);
for k=1:i
    BDT{k} = BDTemp{k};
end

