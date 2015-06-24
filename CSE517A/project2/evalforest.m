function preds=evalforest(F,xTe)
% function preds=evalforest(F,xTe);
%
% Evaluates a random forest on a test set xTe.  
%
% input: 
% F   | Forest of decision trees
% xTe | matrix of m input vectors (matrix size dxm)
%
% output: 
%
% preds | predictions of labels for xTe
%

%% fill in code here

[d,m]= size(xTe);
numTrees = size(F,2);

predictionMatrix = zeros(numTrees,m);

for i = 1:numTrees
   predictionMatrix(i,:) = evaltree(F{i},xTe);
end

% Sinces trees are diverse both in data sampled and features split on
% simply taking the mode is a good indication of the best prediction
preds = mode(predictionMatrix,1);


%% Dummy Code written by a dummy, namely, shane
% 
% % Some Constants
% [d,m] = size(xTe);
% numTrees = size(F);
% 
% weightMatrix = zeros(d,numTrees);
% 
% evalVect = ones(1,numTrees);
% for i = 1:numTrees
%     % Get result of each tree from forest
%     evalVect(i) = evalTree(F(i),xTe);
%    
%     % Get the tree
%     T = F(i);
%     
%     % Enter weighted features as column in weight matrix
%     weightMatrix(T(2,:),i) = evalVect(i);
% end
% 
% % Get weight vector by taking average error per average feature error
% weightMatrix = weightMatrix./sum(weightMatrix~=0,2)';
% weights = sum(weightMatrix,2)./sqrt(sum(sum(weightMatrix,2).^2,1));
% 
% % Build a new tree using weights
% % wait, you can't. fuck


