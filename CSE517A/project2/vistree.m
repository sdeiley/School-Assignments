function vistree(T,rc,colors)
% function vistree(T,depth,colors)
% visualizes tree T
%
% INPUT:
% T  : decision tree
% depth : depth to visualize
% colos : cell-array of rgb color values for each class 
% 

if ~(exist('rc')==1) || isempty(rc),rc=inf;end;
if ~(exist('colors')==1),colors=[];end;
ax=axis;
box on;
hold on;
boxtree(T,ax,rc,colors);


function boxtree(D,ax,rc,colors)
% function boxtree(D,ax);
%
% Visualizes a tree within a bounding box
%
% Input:
% T  : a decision tree T
% ax : a bounding box [x1 x2 y1 y2]
%

stack(1).index=1;
stack(1).ax=ax;
stack(1).rc=rc;

while ~isempty(stack)
 index=stack(end).index;
 ax=stack(end).ax;
 rc=stack(end).rc;
 
 
 if (D(4,index)~=0)
  c=D(3,index);
  axL=ax;
  axR=ax;
  if D(2,index)==1,
	plot([c c],ax(3:4),'k-');
	axL(2)=c;
	axR(1)=c;
  else
	plot(ax(1:2),[c c],'k-');	
	axL(4)=c;
	axR(3)=c;
  end;
  
  if rc>1
   ls=length(stack);
   stack(ls).index=D(4,index);
   stack(ls).ax=axL;
   stack(ls).rc=rc-1;
   
   stack(ls+1).index=D(5,index);
   stack(ls+1).ax=axR;
   stack(ls+1).rc=rc-1;
  else
     stack=stack(1:end-1);  	
  end;
 else 
   stack=stack(1:end-1);

   if ~isempty(colors)
	% We have reached a leaf and are supposed to color it
	co=colors(D(1,index));
	fill(ax([1 2 2 1]),ax([3 3 4 4]),co{1});
   end;
 end;
end;
