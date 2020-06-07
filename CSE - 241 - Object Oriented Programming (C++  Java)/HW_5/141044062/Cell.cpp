/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
			Cell.cpp
*/

#include <iostream>
#include "Cell.h"

using namespace std;
using CellSpace::Cell;

namespace CellSpace{
	Cell::Cell():row(0),column('A'),whoCell(empty){/*empty*/}

	Cell::Cell(int nrow,char col ,whichCell whos):row(nrow),column(col),whoCell(whos){/*empty*/}

	void Cell::setWhoCell(whichCell newCell){
		whoCell = newCell;
	}
	
	whichCell Cell::getWhoCell()const{
		return whoCell;
	}
	
	void Cell::setCellNumber(int number){
		cellNumber = number;
	}
	
	int Cell::getCellNumber()const{
		return cellNumber;
	}
	
}// CellSpace
