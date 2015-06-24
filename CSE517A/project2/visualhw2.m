function visualhw2
% function visualhw2
% 
% Loads the iris data set and visualizes a decision tree on the first two dimensions
%

load('iris');

% Let's first see the classification rate
tic;

T=id3tree(xTr(1:2,:),yTr,inf);

clf;
% plot the data
h=gscatter(xTr(1,:),xTr(2,:),yTr);
ocolors=[get(h,'Color')];
a=axis;

for i=1:length(ocolors), colors{i}=max(ocolors{i},[0.5 0.5 0.5]);end;

subplot(1,2,1);
cla;
axis(a);
vistree(T,inf,colors);
hold on;	
h=gscatter(xTr(1,:),xTr(2,:),yTr);
set(h,'Marker','o','MarkerSize',5,'MarkerEdgeColor',[0 0 0])
for i=1:length(h)
	set(h(i),'MarkerFaceColor',ocolors{i});
end;
title('Training data');

subplot(1,2,2);
cla;
axis(a);
vistree(T,inf,colors);
hold on;	
h=gscatter(xTe(1,:),xTe(2,:),yTe);
set(h,'Marker','s','MarkerSize',5,'MarkerEdgeColor',[0 0 0])
for i=1:length(h)
	set(h(i),'MarkerFaceColor',ocolors{i});    
end;
title('Testing data');


