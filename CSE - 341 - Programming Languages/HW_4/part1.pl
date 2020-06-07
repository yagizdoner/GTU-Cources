% CSE 341 - HW 4 - Part1 - Yağız Döner - 141044062

flight(edirne,edremit).
flight(erzincan,edremit).
flight(istanbul,rize).
flight(istanbul,van).
flight(istanbul,ankara).
flight(istanbul,gaziantep).
flight(istanbul,antalya).
flight(istanbul,izmir).
flight(izmir,isparta).
flight(isparta,burdur).
flight(rize,van).
flight(ankara,van).
flight(ankara,konya).
flight(konya,antalya).
flight(gaziantep,antalya).

connectedFlight(X,Y) :- flight(X,Y), flight(Y,X).
% Tanımlamaları uzatmamak amacıyla flightları tek
% yön tanımladım ve connectedFlight ile iki yönlü yaptım.

:- dynamic visited/1. 
:- dynamic neighVisited/1.
% bu dinamik değişkenler sayesinde, gezdiğim şehirleri
% ve onların komşu şehirlerini tuttum. Bu şekilde
% sonsuz döngüden kurtuldum.


route(X,Z) :- retractall(visited(_)),retractall(neighVisited(_)),route_helper(X,Z).
route_helper(X,Z) :- connectedFlight(X,Z), assert(visited(X)),
								 not(neighVisited(Z)), assert(neighVisited(Z)).
route_helper(X,Z) :- connectedFlight(X,Y), not(visited(Y)) ,route_helper(Y,Z), not(Z==X).

