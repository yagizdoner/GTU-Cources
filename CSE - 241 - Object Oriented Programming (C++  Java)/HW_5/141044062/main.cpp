/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
		   main.cpp
*/

#include <iostream>
#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourUndo.h"

using namespace std;
using CellSpace::Cell;
using CellSpace::ConnectFourAbstract;
using CellSpace::ConnectFourPlus;
using CellSpace::ConnectFourDiag;
using CellSpace::ConnectFourUndo;

int main(int argc, char** argv) {
	char type;
	cout << "There are 3 types game."<<endl;
	cout << "P is Plus(vertical and horizonal), D is Diagonal and U is Undo."<<endl;
	cout << "Which Type Game Do You Want to Play : ";
	cin >> type;
	while(type != 'P' && type != 'D' && type != 'U'){
		cerr<<"Invalid Type! Enter P - D - U : ";
		cin >> type;
	}
	if(type=='P')
		ConnectFourPlus P;
	else if(type=='D')
		ConnectFourDiag D;
	else // it means that type == U
		ConnectFourUndo U;
	return 0;
	/*
		Objelerin non-parameter constr.larinda playGame fonk. ve duruma gore
		player vs player ya da player vs computer cagrilacak.
	*/
}

