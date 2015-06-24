function [accs,total]=hw2tictoc(filename);

% addpath('../project1')
if exist('filename')~=1,filename='heart';end;
load(filename);

tic;
T=id3tree(xTr,yTr);
te=analyze('acc',yTe,evaltree(T,xTe));
tr=analyze('acc',yTr,evaltree(T,xTr));
tx=toc;
fprintf('D-Tree: Time: %2.2fs Training accuracy %2.2f, Testing accuracy %2.2f \n',tx,tr,te);
accs=[tr;te];

% make train /validation split
itr=ismember(1:length(yTr),randsample(1:length(yTr),ceil(0.8*length(yTr))));

tic;
T=prunetree(id3tree(xTr(:,itr),yTr(:,itr)),xTr(:,~itr),yTr(~itr));
te=analyze('acc',yTe,evaltree(T,xTe));
tr=analyze('acc',yTr,evaltree(T,xTr));
tp=toc;
fprintf('PRUNED: Time: %2.2fs Training accuracy %2.2f, Testing accuracy %2.2f \n',tp,tr,te);
accs=[accs [tr;te]];


tic;
F=forest(xTr,yTr,50);
tr=analyze('acc',yTr,evalforest(F,xTr));
te=analyze('acc',yTe,evalforest(F,xTe));
tf=toc;
fprintf('Forest: Time: %2.2fs Training accuracy %2.2f, Testing accuracy %2.2f\n',tf,tr,te);
accs=[accs [tr;te]];



tic;
BDT=boosttree(xTr,yTr,15,4);
tr=analyze('acc',yTr,evalboost(BDT,xTr));
te=analyze('acc',yTe,evalboost(BDT,xTe));
tb=toc;
fprintf('Boost : Time: %2.2fs Training accuracy %2.2f, Testing accuracy %2.2f\n',tb,tr,te);
accs=[accs [tr;te]];

total=tx+tp+tf;

tic;
teknn=analyze('acc',knnclassifier(xTr,yTr,xTe,3),yTe);
tknn=toc;
fprintf('KNN   : Time: %2.2fs Testing accuracy %2.2f\n',tknn,teknn);


if total>120, fprintf('Your code is currently probably too slow.\n');end;

accs=mean(accs(2,:));