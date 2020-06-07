% CSE 341 - HW 4 - Part2 - Yağız Döner - 141044062

distance(edirne,edremit,235).
distance(erzincan,edremit,1044).
distance(istanbul,rize,970).
distance(istanbul,van,1264).
distance(istanbul,ankara,352).
distance(istanbul,gaziantep,850).
distance(istanbul,antalya,481).
distance(istanbul,izmir,328).
distance(izmir,isparta,307).
distance(isparta,burdur,24).
distance(rize,van,373).
distance(van,ankara,920).
distance(ankara,konya,230).
distance(konya,antalya,191).
distance(gaziantep,antalya,594).

connectedFlight(X,Y,L) :- distance(X,Y,L) ; distance(Y,X,L).
% yine part1 deki gibi uçuşlar çift yönlü yapıldı.

:-dynamic distance/1.						

sroute(X,Y,D) :- retractall(distance(_)), sroute_helper(X,Y,D).

sroute_helper(X,Y,D) :- \+ distance(_),route(X,Y,D1),
						  assert(distance(D1)),sroute_helper(X,Y,D), !. 
						  		% sondaki ! ile aynı sonucun birkaç kere
						  		% tekrar etmesinin önüne geçmiş oldum.						                              
sroute_helper(X,Y,_) :- route(X,Y,D1), distance(D2), D1 < D2,
                        retract(distance(D2)),assert(distance(D1)), false.                                               

sroute_helper(_,_,D) :- distance(D), retract(distance(D)).				

route(X,Y,D) :- connectedFlight(X,Y,D).   
route(X,Y,D) :- findDistance(X,Y,D,[]).
findDistance(X,Y,D,_) :- connectedFlight(X,Y,D).
findDistance(X,Y,D,L) :- \+ isMember(X,L), connectedFlight(X,Z,D1), 					
							findDistance(Z,Y,D2,[X|L]), not(X==Y), D is D1+D2.

% part4 de kullanılan predicate.
isMember(X, [X|_]).       
isMember(X, [_|Tail]) :- isMember(X, Tail).