function [ypredict]=evaltree(T,xTe)
% function [ypredict]=evaltree(T,xTe);
%
% input: 
% T0  | tree structure
% xTe | Test data (dxn matrix)
%
% output: 
%
% ypredict : predictions of labels for xTe
%

%% fill in code here

% Initialize prediction vector
ypredict = zeros(1,length(xTe));

for i = 1:length(xTe)
    t = 1; %test position
    while 1
        try a=T(4,t);
        catch
            1;
        end
        if t == 0 || T(4,t) ==0
            ypredict(i) = T(1,t);
            break;
        end
        f = T(2,t); c = T(3,t);
        if xTe(f,i) <=c
            t = T(4,t);
        else
            t = T(5,t);
        end
    end
end
