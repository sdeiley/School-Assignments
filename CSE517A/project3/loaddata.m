function loaddata(directory,output)

if nargin<1,directory='data_train';end;
if nargin<2,output='data_train';end;

%% tokenization (X)

% Uncomment these lines of you want to do tokenization yourself

if 1 % change this to 1 if you want to change the tokenization
 fprintf('Running python tokenization script ...\n');
 system(['python tokenize.py ' directory ' 10 > spamdata.csv']);
 fprintf('Loading data ...\n');
 M=load('spamdata.csv');
 
 % normalize the colums to sum to 1
 X=sparse(M(:,2),M(:,1),ones(length(M),1));
 X=X*(spdiags(1./sum(X)',0,size(X,2),size(X,2)));
 clear('M');

 % Load in labels (do not change this part of the code)
 [label,paths]=textread([directory '/index'],'%s %s');
 Y=cellfun(@(x) isequal(x,'spam')*2-1,label,'UniformOutput',true)';    
 clear('label');

 save([output '.mat'],'X','Y');
end;




