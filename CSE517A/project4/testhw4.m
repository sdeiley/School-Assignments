function [testerr,graderr]=testhw4;

load boston;
wst=[1 12 size(xTr,1)];
w=initweights(wst);

[xTr,xTe]=preprocess(xTr,xTe);
graderr=checkgrad('ffnn',w,1e-05,xTr,yTr,wst)
[w,l]=minimize(w,'ffnn',100,xTr,yTr,wst);


if graderr<1e-05,
        disp('Gradient looks good. Implementation probably correct!');
else
        disp('Error! Gradient incorrect!!!');
end;

trainerr=sqrt(mean((ffnn(w,xTr,[],wst)-yTr).^2));
testerr=sqrt(mean((ffnn(w,xTe,[],wst)-yTe).^2));
