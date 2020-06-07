/*
	Yagiz Doner - 141044062 
	    CSE 241 - HW_5
	   ConnectFourUndo.h
*/

#ifndef CONNECTFOURUNDO_H
#define CONNECTFOURUNDO_H

#include <iostream>

namespace CellSpace{
	class ConnectFourUndo : public ConnectFourAbstract {
		public:
			ConnectFourUndo();
			void vsUsers();
			void vsComputer();
			bool horizonalCheck();
			bool verticalCheck();
			bool totalCheck(); 
	};
} // CellSpace
#endif //CONNECTFOURUNDO_H
