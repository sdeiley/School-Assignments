load boston;

[xTr,xTe]=preprocess(xTr,xTe);

SIGMA=7;
LAMBDA=0.04;


%% do training

figure(1);
clf
[iv,itr]=sort(yTr);
[iv,ite]=sort(yTe);

subplot(1,3,1);
plot(yTr(itr),'r-','LineWidth',5);
title('TRAIN');
hold on;
drawnow;
htr=plot(yTr(itr),'k.','Visible','off');
subplot(1,3,2);
plot(yTe(ite),'r-','LineWidth',5);
title('TEST');
hold on;
drawnow;
hte=plot(yTe(ite),'k.');
set(hte,'Visible','off');
set(htr,'Visible','off');

subplot(1,3,3);
herr=plot(zeros(4));


%% kernel regression
 
 [predTe,predTr]=rbfkernelregress(xTr,yTr,xTe,SIGMA,LAMBDA);
 set(hte,'YData',predTe(ite),'Visible','on');
 set(htr,'YData',predTr(itr),'Visible','on'); 
 
 errTr=[mean((predTr(:)-yTr(:)).^2)];
 errTe=[mean((predTe(:)-yTe(:)).^2)];
 
 cla;
 plot([0,1],[errTr,errTr],'b-');
 hold on;
 plot([0,1],[errTe,errTe],'g-');
 axis([0 1 0 30]);
 
 title('RMSE Errors');
 drawnow;

fprintf('Lowest train score: %2.4f\n',min(errTr));
fprintf('Lowest test score: %2.4f\n',min(errTe));
