/*
	Yagiz Doner - 141044062 
	    CSE 241 - HW_5
	   ConnectFourPlus.h
*/

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include <iostream>

namespace CellSpace{
	class ConnectFourPlus : public ConnectFourAbstract {
		public:
			ConnectFourPlus();
			void vsUsers();
			void vsComputer();
			bool horizonalCheck();
			bool verticalCheck();
			bool totalCheck(); 
	};
} // CellSpace
#endif //CONNECTFOURPLUS_H
