function [preds]=linclassify(w,xTe)
% function w=ridge(xTr,yTr,lambda)
%
% INPUT:
% w weight vector (default w=0)
% xTe dxn matrix (each column is an input vector)
%
% OUTPUTS:
% 
% preds predictions
% 

[d,n]=size(xTe);

preds = w'*xTe;
% disp(preds);
% for i = 1:length(preds)
%     if preds(i)>0
%         preds(i)=1;
%     elseif preds(i)<0
%         preds(i)=-1;
%     end
% end
