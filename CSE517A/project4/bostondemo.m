load boston;

ROUNDS=200;
ITER=50;
STEPSIZE=0.01;
wst=[1 24 size(xTr,1)];


[xTr,xTe]=preprocess(xTr,xTe);

%% do training
w=initweights(wst);

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
legend('train','test');

errTr=[];
errTe=[];

f=@(w) ffnn(w,xTr,yTr,wst);
for i=1:ROUNDS
 %[w,l]=minimize(w,'ffnn',ITER,xTr,yTr,wst);
 w=grdescent(f,w,STEPSIZE,ITER,1e-8);
 predTr=ffnn(w,xTr,[],wst);
 predTe=ffnn(w,xTe,[],wst);
 set(hte,'YData',predTe(ite),'Visible','on');
 set(htr,'YData',predTr(itr),'Visible','on'); 
 %subplot(1,3,3);
 errTr=[errTr sqrt(mean((predTr(:)-yTr(:)).^2))];
 errTe=[errTe sqrt(mean((predTe(:)-yTe(:)).^2))];
 %plot([errTr' errTe']);
 axis([0 ROUNDS 0 max(max(errTe),max(errTr))]);
 d={};
 set(herr(1),'YData',errTr);
 set(herr(2),'YData',errTe);
 title('RMSE Errors');
 drawnow;
end;

fprintf('Lowest train score: %2.4f\n',min(errTr));
fprintf('Lowest test score: %2.4f\n',min(errTe));
