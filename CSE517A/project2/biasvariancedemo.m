function [lbias,lvariance,lnoise,ltotal]=biasvariancedemo(makeplot)
% function [bias,variance,noise]=biasvariancedemo(makeplot)
% 
% This function generates a 2d data set from two Gaussian distributions
% and trains decision trees of varying max-depth. 
% The "total" error is decomposed into "bias", "variance", "noise".
%
% INPUT:
% makeplot | default=true (allows you to switch off the plotting)
%

%% define global variables
if nargin<1, makeplot=true;end;
global Nsmall Nbig NMODELS OFFSET;
Nsmall=500; % how big is the training set size N
Nbig=100000; % how big is a really big data set (approx. infinity)
NMODELS=25; % how many models do you want to average over
OFFSET=2;   % offset between the two gaussians
MAXDEPTH=10;% maximum depth of the most complex decision tree model


if makeplot,
 %% Visualize data
 close all;
 clf;
 [xTr,yTr]=toydata(OFFSET,1000);
 scat(xTr,2,yTr);
 colorbar;
 title('Data set from two Gaussians');
 disp('Please press a key ...');
 pause;
 clf;
end;


%% Different depth classifiers
for md=2:MAXDEPTH
    % use this data set as an approximation of the true test set
    [xTe,yTe]=toydata(OFFSET,Nbig);

    
    %% Estimate AVERAGE ERROR (TOTAL)
    total=0;
    for j=1:NMODELS
        [xTr2,yTr2]=toydata(OFFSET,Nsmall);        
        Tsmall=id3tree(xTr2,yTr2,md);
        total=total+mean(evaltree(Tsmall,xTe)~=yTe);
    end;
    total=mean(total)/NMODELS;

    
    %% Estimate Noise
    ybar=computeybar(xTe);
    noise=mean((yTe-ybar).^2);
    
    %% Estimating BIAS
    hbar=computehbar(xTe,md);
    bias=mean((hbar-ybar).^2);
    
    
    %% Estimating VARIANCE
    variance=computevariance(xTe,md,hbar);
    
    
    
    %% print and store results
    lbias(md)=bias;
    lvariance(md)=variance;
    ltotal(md)=total;
    lnoise(md)=noise;
    lsum(md)=lbias(md)+lvariance(md)+lnoise(md);
    fprintf('MaxDepth %i: Bias: %2.4f Variance: %2.4f Noise: %2.4f Total: %2.4f\n',md,lbias(md),lvariance(md),lnoise(md),ltotal(md));
    
    %% plot results
    if makeplot & md>2
     figure(1);
     hold on;
     plot(2:md,lbias(2:end),'r-','LineWidth',2);
     plot(2:md,lvariance(2:end),'k-','LineWidth',2);
     plot(2:md,lnoise(2:end),'g-','LineWidth',2);
     plot(2:md,ltotal(2:end),'b-','LineWidth',2);
     plot(2:md,lsum(2:end),'k--','LineWidth',2);
     legend('Bias','Variance','Noise','Test error','Bias+Var+Noise');
     xlabel('Maxdepth');
     ylabel('Squared Error');
     set(gca,'XTick',2:md);
     set(gca,'FontSize',18);
     drawnow;
    end;
end;

