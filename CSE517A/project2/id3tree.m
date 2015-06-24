function T=id3tree(xTr,yTr,maxdepth,weights)
% function T=id3tree(xTr,yTr,maxdepth,weights)
%
% The maximum tree depth is defined by "maxdepth" (maxdepth=2 means one split). 
% Each example can be weighted with "weights". 
%
% Builds an id3 tree
%
% Input:
% xTr | dxn input matrix with n column-vectors of dimensionality d
% xTe | dxm input matrix with n column-vectors of dimensionality d
% maxdepth = maximum tree depth
% weights = 1xn vector where weights(i) is the weight of example i
% 
% Output:
% T = decision tree 
%

%% fill in code here

%Question a: for a data set of size n, a tree of depth h=log2(n) is needed,
%with 2^(h+1)-1 nodes maximum at that height
[d,n] = size(xTr);

if nargin<4,
    weights=ones(1,n)./n;
end;

if nargin<3
    if log2(n) > d + 1
        numnodes = 2^(d + 2) - 1;
    else
        numnodes = 2^(log2(n)+1)-1;
    end
else
    if log2(n) <= d + 1
        if maxdepth<=log2(n) %Check to make sure maxdepth doesn't exceed max possible binary splits
            numnodes = 2^(maxdepth+1)-1;
        else
            numnodes = 2^(log2(n)+1)-1;
        end
    else 
        if maxdepth <= d + 1
            numnodes = 2^(maxdepth+1)-1;
        else
            numnodes = 2^(d+2)-1;
        end
    end
end

% Initialize T with estimate of maximum possible size for speed
numnodes = cast(numnodes,'int32')+1;
T = zeros(6,numnodes);

nextsub = 2; %index of next subtree
data = cell(1,numnodes);
data{1}.x = xTr; data{1}.y = yTr;
i = 1;
while 1
    xset = data{i}.x;
    yset = data{i}.y;
    [feature,cut,Hbest] = entropysplit(xset,yset,weights);
    if feature~=0 && size(xset,2)~=1
        T(1,i) = mode(yset);
        T(2,i) = feature;
        T(3,i) = cut;
        T(4,i) = nextsub;

        posIndices = 1:size(xset,2);
        leftind = posIndices(xset(feature,:)<=cut);
        rightind = posIndices(xset(feature,:)>cut);
        data{nextsub}.x = xset(:,leftind);
        data{nextsub}.y = yset(:,leftind);
        T(6,nextsub) = i;
        
        if (nextsub+2)>numnodes
            T(4:5,i)=0;
        else
            nextsub = nextsub+1;
        end

        data{nextsub}.x = xset(:,rightind);
        data{nextsub}.y = yset(:,rightind);
        T(5,i) = nextsub;
        T(6,nextsub) = i;
        
        if (nextsub+1)>numnodes
            T(4:5,i)=0;
        else
            nextsub = nextsub+1;
        end
    else
        T(1,i) = mode(yset);
    end

    i = i+1;
    if i==nextsub || i>numnodes
        T(:,i:end) = [];
        break;
    end
end
        
    



