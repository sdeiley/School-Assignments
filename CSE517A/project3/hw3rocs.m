function hw3rocs

load('data_train');
valsplit;

MAXITER=1000;
STEPSIZE=1e-2;
clf
set(gca,'FontSize',18);
xlabel('False Positive Rate');
ylabel('True Positive Rate');
box on;
hold on;
% 
%% Ridge Regression
disp('Ridge Start')
[d,n]=size(xTr);
ws=grdescent(@(w) ridge(w,xTr,yTr,0.1),zeros(d,1),STEPSIZE,MAXITER);

preds=linclassify(ws,xTv);
[fpr,tpr,th,sqauc]=perfcurve(yTv,preds,1);
plot(fpr,tpr,'b','LineWidth',4);
drawnow;

%% Hinge Loss
disp('Hinge Start');
[d,n]=size(xTr);
wh=grdescent(@(w) hinge(w,xTr,yTr,0.1),zeros(d,1),STEPSIZE,MAXITER);

preds=linclassify(wh,xTv);
[fpr,tpr,th,hinauc]=perfcurve(yTv,preds,1);
plot(fpr,tpr,'g','LineWidth',4);
drawnow;

%% Logistic Regression
disp('Log Start');
[d,n]=size(xTr);
wl=grdescent(@(w) logistic(w,xTr,yTr),zeros(d,1),STEPSIZE,MAXITER);

preds=linclassify(wl,xTv);
[fpr,tpr,th,logauc]=perfcurve(yTv,preds,1);
plot(fpr,tpr,'r','LineWidth',4);
drawnow;



fprintf('Hinge loss: Area under the curve: %2.2f\n',hinauc);
fprintf('Logistic loss: Area under the curve: %2.2f\n',logauc);
fprintf('Squared loss: Area under the curve: %2.2f\n',sqauc);
axis equal;axis tight;
legend('ridge','hinge','logistic');
