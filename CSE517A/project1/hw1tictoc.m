function [result,totaltime]=hw1tictoc()
% function details=hw1tictoc()
%
% 

fprintf('Face Recognition: (1-nn)\n')
load('faces');
tic;
preds=knnclassifier(xTr,yTr,xTe,1);
result=analyze('acc',yTe,preds);
totaltime=toc;
fprintf('You obtained %2.2f%% classification acccuracy in %2.4f seconds\n',result*100.0,totaltime);

fprintf('\n');
fprintf('Handwritten digits Recognition: (3-nn)\n')
load('digits');
tic;
preds=knnclassifier(xTr,yTr,xTe,3);
result=analyze('acc',yTe,preds);
totaltime=toc;
fprintf('You obtained %2.2f%% classification acccuracy in %2.1f seconds\n',result*100.0,totaltime);




