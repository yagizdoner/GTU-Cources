/*
	Yagiz Doner - 141044062 
	    CSE 241 - HW_5
	   ConnectFourDiag.h
*/

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include <iostream>

namespace CellSpace{
	class ConnectFourDiag : public ConnectFourAbstract {
		public:
			ConnectFourDiag();
			void vsUsers();
			void vsComputer();
			bool diagonalCheck();
	};
} // CellSpace
#endif //CONNECTFOURDIAG_H
