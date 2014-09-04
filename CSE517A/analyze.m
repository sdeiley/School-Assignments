% Author: Shane Deiley (and Mark Heimann)
% January 29th, 2014

function output=analyze(kind,truth,preds)	
% function output=analyze(kind,truth,preds)		
%
% Analyses the accuracy of a prediction.
% Input:
% kind='acc' classification error
% kind='abs' absolute loss
% (other values of 'kind' will follow later)

switch kind
	case 'abs'
		% compute the absolute difference between truth and predictions
		output=sum(abs(truth-preds))/length(truth);
		
	case 'acc' 
		% compute the classification error between truth and predictions
        temp = truth - preds;
        if isempty(temp)
            error('divide by zero error')
        end;
        nonZero = find(temp);
        output = 1 - (length(nonZero)/length(temp));
        
        
		 	
end;

