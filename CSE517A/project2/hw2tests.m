function [r,s]=hw2tests()
% function [r,s]=hw2tests()
%
% Tests the functions from homework assignment 1
% Please make sure that the error statements are instructive. 
%
% Output: 
% r=0 number of tests that broke
% s= statement describing the failed test (s={} if all succeed)
%


% Put in any seed below
rand('seed',31415926535);
% initial outputs
r=0;
s={};


% Example:
% Check if xor data is split correctly. 

x=[  0     1     0     1
     1     0     0     1];
y =[  2     2     1     1];
[f,c]=entropysplit(x,y);
if c<=0 || c>1,			% if test failed ...
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='First XOR split not correct.';
end;


x=[  0     0
     1     0];
y =[  2    1];
[f,c]=entropysplit(x,y);
if f~=2,			% if test failed ...
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='In the XOR 2nd split, it splits on the wrong feature.';
end;

if f==1 & (c<=1 | c>0),			% if test failed ...
	r=r+1;				% set output conditions and exit
	s{length(s)+1}='2nd XOR split feature is correct, but the cut value is wrong.';
end;


