/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
	  ConnectFourDiag.cpp
*/

#include <iostream>
#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"

using namespace std;
using CellSpace::Cell;
using CellSpace::ConnectFourAbstract;
using CellSpace::ConnectFourDiag;

namespace CellSpace{
	ConnectFourDiag::ConnectFourDiag(){
		undo = 0; // undo fonk. cagirilmasin diye.
		playGame();
		if(style == 'P')
			vsUsers();
		else if(style == 'C')
			vsComputer();
	}
	void ConnectFourDiag::vsUsers(){
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
		}while(diagonalCheck() != 1);
		
		winningMessage();
	}
	
	void ConnectFourDiag::vsComputer(){
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
		}while(diagonalCheck() != 1);
		
		winningMessage();
	}
	
	bool ConnectFourDiag::diagonalCheck(){
		int row,col,k;
		whichCell letter;
		for(row=getRow()-1 ;row>=3; --row){	
			// r>=3; olmasinin nedeni; üstteki ilk 3 satirdan diagonal olarak 4lu bir grup gelememesi.
			// yani bosa arama yapmýyor.
			for(col=0 ;col<getColumn(); ++col){
				if(gameBoard[row][col].getWhoCell() != empty && gameBoard[row][col].getWhoCell() != unused){
					letter = gameBoard[row][col].getWhoCell() ;
					// sag ust capraz durumu.
					if(gameBoard[row-1][col+1].getWhoCell() == letter && gameBoard[row-2][col+2].getWhoCell() == letter && gameBoard[row-3][col+3].getWhoCell() == letter){
						if(letter == user1){
							for(k=0;k<4;++k)
								gameBoard[row-k][col+k].setWhoCell(finish1);	
						}
						else if(letter == user2){
							for(k=0;k<4;++k)
								gameBoard[row-k][col+k].setWhoCell(finish2);	
						}
						else if(letter == computer){
							for(k=0;k<4;++k)
								gameBoard[row-k][col+k].setWhoCell(finish3);	
						}
						return 1;
					}
					// sol ust capraz durumu
					else if(gameBoard[row-1][col-1].getWhoCell() == letter && gameBoard[row-2][col-2].getWhoCell() == letter && gameBoard[row-3][col-3].getWhoCell() == letter){
						if(letter == user1){
							for(k=0;k<4;++k)
								gameBoard[row-k][col-k].setWhoCell(finish1);	
						}
						else if(letter == user2){
							for(k=0;k<4;++k)
								gameBoard[row-k][col-k].setWhoCell(finish2);	
						}
						else if(letter == computer){
							for(k=0;k<4;++k)
								gameBoard[row-k][col-k].setWhoCell(finish3);	
						}
						return 1;
					}
				}
			}
		}
		return 0;
	}
}// CellSpace
