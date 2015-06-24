function T=prunetree(T,xTe,y)
% function T=prunetree(T,xTe,y)
%
% Prunes a tree to minimal size such that performance on data xTe,y does not
% suffer.
%
% Input:
% T = tree
% x = validation data x (dxn matrix)
% y = labels (1xn matrix)
%
% Output:
% T = pruned tree 
%

%% fill in code here

% Initial Test Error
Eval = analyze('acc',y,evaltree(T,xTe));

% Boolean for loop
pruned = 0;

% Constant marking prune storage vector index
p = 1;

% Initialization of vector of leaves to remove
% prune = zeros(6,size(T,2));

% Process:
% 1. Pull all current leaves into vector
% 2. For each leave pair, test to see if it lowers error
% 3. Restructure tree if any leaves need pruning
% 4. If a prune occurred, restart process.
while 1
    
    % Leaves Vector
    leaves = find(T(4,:)==0);
    
    % Iterate through the leaves testing if they lower error
    for i = 1:length(leaves)

        % If sibling is not leaf
        try q=[T(4,T(5,T(6,leaves(i)))) T(4,T(4,T(6,leaves(i))))];
            if ~((T(4,T(5,T(6,leaves(i)))) == 0) && (T(4,T(4,T(6,leaves(i)))) == 0))
                continue;
            end
        catch
            1;
        end

        
        % Copy the true tree for evaluation
        Ti = T;

        % Make the parent a leaf for evaltree termination
        try e=Ti(4:5,T(6,leaves(i)));
            Ti(4:5,T(6,leaves(i))) = 0;
        catch
            disp(T(6,leaves(i)));
        end

        % New Error without leave pair
        testEval = analyze('acc',y,evaltree(Ti,xTe));

        if testEval >= Eval
            pruned = 1;

            % Add leaf to prune queue
            prune(1,p) = T(6,leaves(i));
            prune(2,p) = leaves(i);
            p = p+1;
        end

    end
    
    if pruned == 1
        % Update T with any prunes
        
        % Make parents into new leaves
        try b = T(5,unique(prune(1,:)));
            T(4,unique(prune(1,:))) = 0;
            T(5,unique(prune(1,:))) = 0;
        catch
            disp(unique(prune(1,:)));
            disp(prune(1,:));
        end;
        
        % Mark all leaves to be pruned as dummy
        try T(:,prune(2,:)) = -1;
        catch 1;
        end
        

% 
%         % Next update indices in T
%         m = size(T,2);
%         j=2;
%         numRemoved=0;
%         while j<m
%             
%             if (T(6,j) ~= -1) && (T(4,j) ~= 0)
%                 % Get number of leaves being removed between parent and i
%                 % Find nodes being removed between j and right child
%                 try toRemove = length(find(T(6,j:T(5,j)) == -1));
%                 catch
%                     disp('zero index');
%                 end
% 
%                 
%                 % Change parent's child index
%                 T(4:5,j) = T(4:5,j)-toRemove;
%                 % Change childrens parent index
%                 try T(6,T(4:5,j))=j;
%                 catch
%                     1;
%                 end
%                 j=j+1;
% %                 if T(4,T(6,i)) == i
% %                     T(4,T(6,i)) = T(4,T(6,i)) - toRemove;
% %                 else
% %                     T(5,T(6,i)) = T(5,T(6,i)) - toRemove;
% %                 end
%                 
% %                 i = i - 1;
%             elseif T(6,j)==-1
%                 % Remove from T
%                 T = T(:,[1:j-1 j+1:size(T,2)]);
%                 T(4:6
%                 j=j+1;
%                 m = size(T,2);
%             else
%                 j=j+1;
%             end
%             
%         end
%         
        % Update eval after making new tree
        Eval = analyze('acc',y,evaltree(T,xTe));

        % Update constants
        p = 1;
        pruned = 0;
        prune = [];
        
    else
        % No leaves lowered error, so return T
        break;
    end
end
    
    