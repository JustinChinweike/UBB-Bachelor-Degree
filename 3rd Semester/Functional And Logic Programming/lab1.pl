%[]
%[H | T]
%example a list [ 1,2,a,b,5]
% H = 1
% T = [ 2, a, b, 5]
% N = 4
% N =:=4
% N is 1+2 (this perform the operation and bound the result to N)
%
%
% Example:
% mutiply the elements of a list with a constant k .
% [1,2,3], k =0 => [10,20,30]
% mulk (L-list, k-number, R - result list)
% %flow model (i , i ,o) ( i, i , i)
mulk([], K,R):-
    R=[].
mulk([H|T], K, R):-
    H1 is H*K,
    mulk(T, K, TR), % ( i,i, o)
    R=[H1|TR].
%
%Mathematical model

%mulk (l1, l2...ln, k) =

%Empty, if n = 0
% {l1.k} U mulk(l2...ln,k), n > 0






