% CSE 341 - HW 4 - Part3 - Yağız Döner - 141044062

enroll(a,102).
enroll(a,108).
enroll(b,102).
enroll(c,108).
enroll(d,341).
enroll(e,455).

when(102,10).
when(108,12).
when(341,14).
when(455,16).
when(452,17).  %tabloda 452 yazılmış, örneklerde 456 kabul edilmiş. Ben 452 olarak kullandım.

where(102,z23).
where(108,z11).
where(341,z06).
where(455,207).
where(452,207).

schedule(S,P,T) :- enroll(S,P), when(P,T).

usage(P,T) :- where(T, P).

conflict(X,Y) :- when(X,T1) , when(Y,T2) , where(X,P1) , where(Y,P2) , (=(T1,T2); =(P1,P2)).
%classların time ları ve bulundukları roomlar alınır. 2 sinden birinde bir çakışma var mı (OR) diye bakılır.


meet(X,Y) :- enroll(X,C1) , enroll(Y,C2) , 
				when(C1,T1) , when(C2,T2) , where(C1,P1) , where(C2,P2) , 
					(=(T1,T2), =(P1,P2)).
%studentların classları çekilir ve bu classların
%time ları ve bulundukları roomlar alınır. 2 si birden çakışıyor (AND) mu diye bakılır.