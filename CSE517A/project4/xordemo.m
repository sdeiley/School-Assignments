function xordemo(wst,rounds);


STEPSIZE=10;
figure(3);
clf;
subplot(1,2,1);
if nargin<1,wst=[1 12 2];end;
if nargin<2,    
    rounds=100;
    if exist('minimize.m')==2,rounds=10;end;
end;
% wst=[1 2]; % compare with this linear model
w=initweights(wst);
ITER=50;

[x,y]=genxor();	
[xx,yy]=meshgrid(-1:0.1:1,-1:0.1:1);  
subplot(1,2,2);
hs=surf(xx,yy,zeros(size(xx)));
axis equal;
title(['Network Layers: ' num2str(wst)]);

subplot(1,2,1);
h=scatter(x(1,:),x(2,:),30,ones(size(y)),'filled')
axis equal;
set(h,'MarkerEdgecolor',[0.5 0.5 0.5])
box on;
colorbar;
drawnow;

f=@(w) ffnn(w,x,y,wst);
for i=1:rounds
 if(exist('minimize.m')==2),
  [w,l]=minimize(w,'ffnn',ITER,x,y,wst);
 else
  w=grdescent(f,w,STEPSIZE,ITER,1e-8);
 end;
 pred=ffnn(w,x,[],wst);
 set(h,'CData',pred)
 drawnow;
 ps=reshape(ffnn(w,[xx(:) yy(:)]',[],wst),length(xx),length(xx));
 set(hs,'ZData',ps);
 drawnow;
end;
	
	
function [x,y]=genxor()

x=randn(2,1000).*0.1;
x(1,251:500)=x(1,251:500)+1;
x(2,501:750)=x(2,501:750)+1;
x(1,751:1000)=x(1,751:1000)+1;
x(2,751:1000)=x(2,751:1000)+1;
y=[ones(1,250) zeros(1,500) ones(1,250)];
x=x-repmat(mean(x,2),1,1000);