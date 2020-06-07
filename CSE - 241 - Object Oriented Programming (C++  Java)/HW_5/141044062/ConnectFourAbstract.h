/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
	 ConnectFourAbstract.h
*/

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Cell.h"

using namespace std;


namespace CellSpace{
	class ConnectFourAbstract {
		public:			
			void playGame();	
			void play();
			void play(int ignore);
			void save(char name[16])const;
			void load(char name[16]);
			void funcUndo();
			void putPc();
			void winningMessage()const;
			void printBoard()const;
			void createBoard(int r, int c);
			bool boardIsEmpty()const;
			bool isSimilar(const char str1[16],const char str2[16])const;
			void changeBoard(whichCell letter, int col);
			void ifLegal(int & col, char & col_name);
			void devine(string str, char first[16], char second[16]);
			int convertCharToInt(const char c)const;
			bool columnIsEmpty(int col)const;
			char toUpperCase(char c)const;
			int getRow()const;
			int getColumn()const;
			inline static void setLivingCell(int n){livingCell += n;}
			inline static int getLivingCell(){return livingCell;}
			~ConnectFourAbstract();
		protected:
			int undo; // undo sadece Undo objesinde 1 olacak.
			char style; // User vs User  or   User vs Computer.
			int turn; // Save Load da sira kimde?
			Cell ** gameBoard;
		private:
			static int livingCell;
			int row;
			int column;
			
	};
} // CellSpace
#endif //CONNECTFOURABSTRACT_H
