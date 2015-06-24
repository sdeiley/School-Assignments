function F=forest(x,y,nt)
% function F=forest(x,y,nt)
%
% INPUT: 
% x | input vectors dxn
% y | input labels 1xn
%
% OUTPUT:
% F | Forest
%

%% fill in code here

[d,n] = size(x);
F = cell(1,nt);
maxdepth = 4;


%weights = ones(1,d);
for i = 1:nt
    % First step of Random Forest Algorithm: Sample with Replacement
    [sampledX, indicesOfSampledX] = datasample(x, size(x,2),2);
    sampledY = y(indicesOfSampledX);
    
    % Randomly make 1/3 of the features' weight 0
%     weights(datasample(1:d,floor(d/3), 'Replace', false)) = 0;
    randomFeatures = datasample(1:d,floor(d/3), 'Replace', false);
    
    sampledX(randomFeatures,:) = 0;
    
    % Generate xTe and yTe for validation in prunetree
    xTe = x(:,~ismember(1:n,unique(indicesOfSampledX)));
    yTe = y(~ismember(1:n,unique(indicesOfSampledX)));
    
    % Adjust weights so they sum to one
%     weights = weights./sum(weights~=0);
    
    % Next, build tree with limited maxdepth
    tree = id3tree(sampledX,sampledY,maxdepth);
    
    % Put in forest pruned tree
    F{i} = prunetree(tree,xTe,yTe);
%    disp(i)
end




