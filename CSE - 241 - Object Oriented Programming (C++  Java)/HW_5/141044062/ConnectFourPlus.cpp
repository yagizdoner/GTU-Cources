/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
	  ConnectFourPlus.cpp
*/

#include <iostream>
#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"

using namespace std;
using CellSpace::Cell;
using CellSpace::ConnectFourAbstract;
using CellSpace::ConnectFourPlus;

namespace CellSpace{
	ConnectFourPlus::ConnectFourPlus(){
		undo = 0; // undo fonk. cagirilmasin diye.
		playGame();
		if(style == 'P')
			vsUsers();
		else if(style == 'C')
			vsComputer();
	}
	void ConnectFourPlus::vsUsers(){
		turn = 1;
		style='P';
		do{
			if(boardIsEmpty()){
				if(turn==1 && style=='P' ){
	    			play(1);
	    			turn=2;
	    		}
	    		else if(turn==2 && style=='P'){
	    			play(1);
	    			turn=1;
				}
	    	}
			else{
				cout << "Nobody Win This Game." << endl;
				return;
			}
		}while(totalCheck() != 1);
		
		winningMessage();
	}
	
	void ConnectFourPlus::vsComputer(){
		turn = 1;
		style='C';   
	
	    do{
			if(boardIsEmpty()){
				if(turn==1 && style=='C'){
	    			play();
	    			turn=2;
	    		}
	    		else if(turn==2 && style=='C'){
	    			play();
	    			turn=1;
				}
	    	}
			else{
				cout << "Nobody Win This Game." << endl;
				return;
			}
		}while(totalCheck() != 1);
		
		winningMessage();
	}
	
	bool ConnectFourPlus::horizonalCheck(){
		int r,c, k;
		// r is row, c is column, k is a counter.
		whichCell letter;
		for(r=getRow()-1 ;r>=0; --r){
			for(c=0 ;c<getColumn(); ++c){	
				if(gameBoard[r][c].getWhoCell() != empty && gameBoard[r][c].getWhoCell() != unused){
					letter = gameBoard[r][c].getWhoCell() ;
					if(gameBoard[r][c+1].getWhoCell() == letter && gameBoard[r][c+2].getWhoCell() == letter && gameBoard[r][c+3].getWhoCell() == letter){
						if(letter == user1){
							for(k=0;k<4;++k)
								gameBoard[r][c+k].setWhoCell(finish1);	
						}
						else if(letter == user2){
							for(k=0;k<4;++k)
								gameBoard[r][c+k].setWhoCell(finish2);	
						}
						else if(letter == computer){
							for(k=0;k<4;++k)
								gameBoard[r][c+k].setWhoCell(finish3);	
						}
						return 1;
					}
				}
			}
		}
		return 0;
	}
	
	bool ConnectFourPlus::verticalCheck(){
		int r,c, k;
		// r is row, c is column, k is a counter.
		whichCell letter;
		for(c=0 ;c<getColumn(); ++c){
			for(r=getRow()-1 ;r>=3; --r){	
				// r>=3; olmasinin nedeni; üstteki ilk 3 satirdan vertical olarak 4lu bir grup gelememesi.
				// yani bosa arama yapmýyor.
				if(gameBoard[r][c].getWhoCell() != empty && gameBoard[r][c].getWhoCell() != unused){
					letter = gameBoard[r][c].getWhoCell() ;
					if(gameBoard[r-1][c].getWhoCell() == letter && gameBoard[r-2][c].getWhoCell() == letter && gameBoard[r-3][c].getWhoCell() == letter){
						if(letter == user1){
							for(k=0;k<4;++k)
								gameBoard[r-k][c].setWhoCell(finish1);	
						}
						else if(letter == user2){
							for(k=0;k<4;++k)
								gameBoard[r-k][c].setWhoCell(finish2);	
						}
						else if(letter == computer){
							for(k=0;k<4;++k)
								gameBoard[r-k][c].setWhoCell(finish3);	
						}
						return 1;					
					}
				}
			}
		}
		return 0;
	}
	
	bool ConnectFourPlus::totalCheck(){
		/* Const olmamasinin nedeni icindeki check fonksiyonlarinin kazanma 
		   durumunda icindeki enum tipi finishlere donusturmesi. 
		   Bu nedenle horizonal-vertical-diagonal checkler const degil.
		*/
		return(horizonalCheck() || verticalCheck());
	} 
}// CellSpace
