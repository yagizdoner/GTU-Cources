% CSE 341 - HW 4 - Part4 - Yağız Döner - 141044062

% In Prolog, Sets are represented as lists.

isMember(X, [X|_]).       
isMember(X, [_|Tail]) :- isMember(X, Tail).
element(E,S) :- isMember(E,S).



union_helper([],A,A). % if first set is empty 
union_helper(A,[],A). % if second set is empty
union_helper([H1|T1], S2, [H1|T2]) :- union_helper(T1, S2, T2). 
% union as S1 , S2.
union_helper(S1, [H1|T1], [H1|T2]) :- union_helper(S1, T1, T2).
% union as S2 , S1.
union(S1,S2,S3) :- union_helper(S1,S2,S3).



intersect_helper(_,[],[]).
intersect_helper([],_,[]).
intersect_helper([H1|T1], S2, S3) :- isMember(H1, S2) , S3 = [H1|T2] , intersect_helper(T1, S2, T2).
intersect_helper([_|T1], S2, S3) :- intersect_helper(T1, S2, S3).
intersect(S1,S2,S3) :- intersect_helper(S1,S2,S3).


equivalent_helper([],[]).
equivalent_helper([H1|T1],[H2|T2]) :- =(H1,H2), equivalent_helper(T1,T2).
equivalent(S1,S2) :- equivalent_helper(S1,S2).