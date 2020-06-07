/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
			Cell.h
*/

#ifndef CELL_H
#define CELL_H

#include <iostream>

enum whichCell{
			empty,
			user1,
			user2,
			computer,
			finish1,
			finish2,
			finish3,
			unused
}; 

namespace CellSpace{
	class Cell {
		public:				
			Cell();
			Cell(int nrow,char col ,whichCell whos);
			void setWhoCell(whichCell newCell);
			whichCell getWhoCell()const;
			void setCellNumber(int number);
			int getCellNumber()const;
		private:
			int cellNumber;         
			/*
				undo isleminde en son hangi pulun eklendigini tutmak icin cellNumber onemli.
				abstract dosyadaki livingCell in durumuna gore her bir Cell e bir number atanacak.
				livingCell her bir cell eklenisinde artarken her bir undo isleminden sonra bir azalacak.
			*/
			char column;
			int row;
			whichCell whoCell;
	};
} // CellSpace
#endif //CELL_H
