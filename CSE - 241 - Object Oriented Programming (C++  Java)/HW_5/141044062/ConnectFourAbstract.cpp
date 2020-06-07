/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_5
	ConnectFourAbstract.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Random Sayi Alabilmek Ýcin
#include "ConnectFourAbstract.h"
#include "Cell.h"

using namespace std;
using CellSpace::Cell;
using CellSpace::ConnectFourAbstract;

int ConnectFourAbstract::livingCell = 0;

namespace CellSpace{
	void ConnectFourAbstract::playGame(){
		int r,c; // r is for row, c is for column.
		char gameStyle;
		cout << "Enter Row Number : ";
		cin >> r;
		while(r<4){
			cerr << "Invalid Row. Enter Bigger than 4. ";
			cin >> r;
		}
		cout << "Enter Column Number : ";
		cin >> c;
		while(c<4 || c>26){ // 26 dan sonra alfabedeki tekli harfler bitiyor.
			cerr << "Invalid Column. Enter Bigger than 4, Smaller than 27 : ";
			cin >> c;
		}
		row = r; // row u set eder.
		column = c; // column i set eder.
		cout << "Enter Game Style (P for Player vs Player // C for Player vs Computer) : ";
		cin >> gameStyle;
		gameStyle = toUpperCase(gameStyle);
		while(gameStyle!='C' && gameStyle!='P'){
			cerr << "Invalid Mod. Enter P / C : ";
			cin >> gameStyle;
			gameStyle = toUpperCase(gameStyle);
		}
		style = gameStyle; // oyun stilini set eder.
		cin.ignore(); // getline sorununu asmak icin.
		createBoard(row,column);
		printBoard();
	}	

	void ConnectFourAbstract::play(){ // Play versusComputer.
		string s1;
		char ld[] = "LOAD";
		char sv[] = "SAVE";
		char un[] = "UNDO";
		char col1[16], col2[16];
		int c1;
		
		if(turn==1){
			cout << "Enter Column for Player or SAVE/LOAD filename : "<<endl ;
			getline(cin,s1);
			devine(s1,col1,col2);
			// save ve load i anlamak icin bu fonk. kullanilir.
			// col1 e save veya load varsa atanýr. col2 ye hangi txt dosyasi oldugu.
			if(isSimilar(col1,sv))
				save(col2);
			else if(isSimilar(col1,ld))
				load(col2);
			else if(isSimilar(col1,un)){
				if(undo==1)
					funcUndo();
				else if(undo==0)
					cerr<<"Undo can't call in these type game.";
			}
			else{
				//eger save-load-undo yoksa gerekli islemleri yapar ve board a pulu ekler.
				s1[0] = toUpperCase(s1[0]);
				c1 = convertCharToInt(s1[0]);
				ifLegal(c1,s1[0]);
				changeBoard(user2,c1);
				printBoard();
			}
		}
		
		if(turn== 2)
			putPc();	
	}

	void ConnectFourAbstract::play(int ignore){ // Play versusPlayers.
		string s;
		char ld[] = "LOAD";
		char sv[] = "SAVE";
		char un[] = "UNDO";
		char col1[16], col2[16];
		int c;
		if(turn==1)	
			cout << "Enter Column for Player 1 or SAVE/LOAD filename : " ; 
		if(turn==2)	
			cout << "Enter Column for Player 2 or SAVE/LOAD filename : " ; 
		getline(cin,s); // girdiði  degeri stringe alir.
		devine(s,col1,col2); 
		if(isSimilar(col1,sv))
			save(col2);	
		else if(isSimilar(col1,ld))
			load(col2);
		else if(isSimilar(col1,un)){
			if(undo==1)
				funcUndo();
			else
				cerr<<"Undo can't call in these type game.";
		}
		else{
			//eger save-load-undo yoksa gerekli islemleri yapar ve board a pulu ekler.
			s[0] = toUpperCase(s[0]);
			c = convertCharToInt(s[0]);
			ifLegal(c,s[0]);
			if(turn==1)					//
				changeBoard(user1,c);   // turn e gore hangi
			else if(turn == 2)			// kullanicinin pulu ekledigine
				changeBoard(user2,c); 	// bakarak pulu ekler.
			printBoard();	
		}
	}
	
	void ConnectFourAbstract::save(char name[16])const{
		int i,j;
		ofstream file;
		file.open(name);
		if(file.fail()){
			cerr << "The Game wasn't Saved. File NOT OPENED !!!" << endl;
			return;
		}

		file<<turn<<endl;			// Kimin sirasi oldugunu kaydetti.
		
		file<<style<<endl;         // Burada oyun tipini txt'ye kaydetti.
		
		file<<row<<endl;  		    // Burada satir sayisini txt ye kaydetti.
		
		file<<column<<endl;        // Burada sutun sayisini txt ye kaydetti.
		
		for(i=0;i<row;++i){            
			for(j=0;j<column;++j){		// Burada Board ' u txt ye kaydetti.
				file<<gameBoard[i][j].getWhoCell()<<endl;		
				file<<gameBoard[i][j].getCellNumber()<<endl;
				//CellNumber Undo islemi icin tutuluyor. 
				}
		}									
		
		file<<getLivingCell()<<endl; // Hali hazirda bulunan Cell sayisini da kaydetti.
		
		cout << "The Game was Saved Successfully. "<<endl;
	
		file.close();
	}
	
	void ConnectFourAbstract::load(char name[16]){
		int i,j,k,n;
		ifstream file;
		file.open(name);
		if(file.fail()){
			cerr << "The Game wasn't Loaded. File NOT FOUND !!!" << endl;
			return;
		}
		
		for(int i=0 ;i<row; ++i) 
			delete [] gameBoard[i] ;      //  Eski Tabloyu Sildi.
		delete [] gameBoard;
		
		file >> turn >> style >> row >> column ;
		
		createBoard(row,column); // bos bir board yapar.
			
		/*
			board u enum type a gore doldurur.
		*/
		for(i=0 ;i<row; ++i){
			for(j=0 ;j<column; ++j){
				file >> k; // Cell in tipine tutmak icin bir variable.
				file >> n; // Cell numarasýný tutmak icin bir variable.
				switch(k){
					case 0: 
						gameBoard[i][j].setWhoCell(empty);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 1:
						gameBoard[i][j].setWhoCell(user1);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 2:
						gameBoard[i][j].setWhoCell(user2);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 3:
						gameBoard[i][j].setWhoCell(computer);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 4:
						gameBoard[i][j].setWhoCell(finish1);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 5:
						gameBoard[i][j].setWhoCell(finish2);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 6:
						gameBoard[i][j].setWhoCell(finish3);
						gameBoard[i][j].setCellNumber(n);
						break;
					case 7:
						gameBoard[i][j].setWhoCell(unused);
						gameBoard[i][j].setCellNumber(n);
						break;
					default:
						break;
				}
			}
		}
		
		file >> n;
		
		setLivingCell(n); // LivingCell set edildi.
		
		cout << "The Game was Loaded Successfully. The Board is Following. \n";
		
		printBoard();
		
		file.close();
	}
		
	void ConnectFourAbstract::funcUndo(){
		int i, j, num;
		
		int greatest = gameBoard[getRow()-1][0].getCellNumber(); // sol alt daki pulun number ini aldi ve digerleri ile karsilastiracak.
		// once en buyuk pulu bulacak.
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0; j<getColumn() ;++j){
				num = gameBoard[i][j].getCellNumber();
				if(num>greatest)
					greatest = num ;
			}
		}
		//sonra buyuk olan pulu empty yapacak.
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0; j<getColumn() ;++j){
				if(gameBoard[i][j].getCellNumber() == greatest){
					gameBoard[i][j].setWhoCell(empty);
					gameBoard[i][j].setCellNumber(0);
				}
			}
		}
		setLivingCell(-1); // 1 pul cikardik.
		printBoard();
	}
		
	void ConnectFourAbstract::putPc(){
		/*
		Computer a karsi durumda Computer in hamlelerini
		yapan fonksiyon fakat 
		Hw 1-2-3 'e gore daha guclendirdim.
		*/
		
		int i, j, num;
			
		/*
			Eger kazanma durumu varsa kazanacak.
		*/
		for(i=getRow()-1 ;i>=3; --i){
			// i nin 3 e kadar olma nedeni board in disina koymaya calistigi zaman segmantation hatasi alir.
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j].getWhoCell()==computer && gameBoard[i-2][j].getWhoCell()==computer && gameBoard[i-3][j].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j);
						printBoard();
						return;
					}						
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j+1].getWhoCell()==computer && gameBoard[i][j+2].getWhoCell()==computer && gameBoard[i][j+3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+3);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j-1].getWhoCell()==computer && gameBoard[i][j-2].getWhoCell()==computer && gameBoard[i][j-3].getWhoCell()==empty){
					if(columnIsEmpty(j-3)){
						changeBoard(computer,j);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j+1].getWhoCell()==computer && gameBoard[i-2][j+2].getWhoCell()==computer && gameBoard[i-3][j+3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+3);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j-1].getWhoCell()==computer && gameBoard[i-2][j-2].getWhoCell()==computer && gameBoard[i-3][j-3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-3);
						printBoard();
						return;
					}
				}
			}
		}
		
		/*
			Eger kaybetme durumu varsa kaybetmemeye calýsacak.
		*/
		for(i=getRow()-1 ;i>=3; --i){
			// i nin 3 e kadar olma nedeni board in disina koymaya calistigi zaman segmantation hatasi alir.
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j].getWhoCell()==user2 && gameBoard[i-2][j].getWhoCell()==user2 && gameBoard[i-3][j].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j+1].getWhoCell()==user2 && gameBoard[i][j+2].getWhoCell()==user2 && gameBoard[i][j+3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+3);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j-1].getWhoCell()==user2 && gameBoard[i][j-2].getWhoCell()==user2 && gameBoard[i][j-3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-3);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j+1].getWhoCell()==user2 && gameBoard[i-2][j+2].getWhoCell()==user2 && gameBoard[i-3][j+3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+3);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j-1].getWhoCell()==user2 && gameBoard[i-2][j-2].getWhoCell()==user2 && gameBoard[i-3][j-3].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-3);
						printBoard();
						return;
					}
				}
			}
		}
		
		/*
			Usttekiler Saglamazsa ikili durumlar devreye girecek. Once Savunacak, Savunamaz ise saldýracak.
		*/
		for(i=getRow()-1 ;i>=2; --i){
			// i nin 2 e kadar olma nedeni board in disina koymaya calistigi zaman segmantation hatasi alir.
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j].getWhoCell()==user2 && gameBoard[i-2][j].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j+1].getWhoCell()==user2 && gameBoard[i][j+2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j-1].getWhoCell()==user2 && gameBoard[i][j-2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j+1].getWhoCell()==user2 && gameBoard[i-2][j+2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j-1].getWhoCell()==user2 && gameBoard[i-2][j-2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j].getWhoCell()==computer && gameBoard[i-2][j].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j+1].getWhoCell()==computer&& gameBoard[i][j+2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j-1].getWhoCell()==computer&& gameBoard[i][j-2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j+1].getWhoCell()==computer && gameBoard[i-2][j+2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+2);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j-1].getWhoCell()==computer && gameBoard[i-2][j-2].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-2);
						printBoard();
						return;
					}
				}
			}
		}
		
		/*
			Tekli durumlar en son ihtimalde calisacak.
		*/
		for(i=getRow()-1 ;i>=1; --i){
			// i nin 1 e kadar olma nedeni board in disina koymaya calistigi zaman segmantation hatasi alir.
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j-1].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-1);
						printBoard();
						return;
					}
				}					
				if(gameBoard[i][j].getWhoCell()==user2 &&gameBoard[i][j+1].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+1);
						printBoard();
						return;
					}
				}					
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j-1].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j-1);
						printBoard();
						return;
					}
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j+1].getWhoCell()==empty){
					if(columnIsEmpty(j)){
						changeBoard(computer,j+1);
						printBoard();
						return;
					}
				}	
				/*
					Hicbir durum olmaz ise random atama yapacak.
				*/
				else{
					num = rand() % getColumn(); //sütun sayýsýna kadar bir sayý verecek.
					while(!columnIsEmpty(num))
						num = rand() % getColumn();
					changeBoard(computer,num);
					printBoard();
					return;
				}	
			}
		}
	}

	
	void ConnectFourAbstract::winningMessage()const{
		int i, j;
		whichCell c;
		printBoard();
		for(i=0 ;i<getRow(); ++i){
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell() == finish1 || gameBoard[i][j].getWhoCell() == finish2 || gameBoard[i][j].getWhoCell() == finish3){
					c = gameBoard[i][j].getWhoCell();
					break;
				}
			}
		}
		// Kimin bitirdigine gore galibiyet mesaji yazar.
		if(c==finish1)
			cout << "Player 1 Win This Game ... " <<endl;
		else if(c==finish2)
			cout << "Player 2 Win This Game ... " <<endl;
		else if(c==finish3)
			cout << "Computer Win This Game ... " <<endl;
	}

	void ConnectFourAbstract::printBoard()const{
		int i,j;
		char k = 'a';
		for(i=0 ;i<column; ++i, ++k)
			cout << k << " ";
		cout << endl;	
		for(i=0 ;i<row; ++i){
			for(j=0;j<column;++j){
				switch(gameBoard[i][j].getWhoCell()){
					case unused:
						cout<<" "<<" ";
						break;
					case empty:
						cout<<"."<<" ";
						break;
					case user1:
						cout<<"X"<<" ";
						break;
					case user2:
						cout<<"O"<<" ";
						break;
					case computer:
						cout<<"X"<<" ";
						break;
					case finish1:
						cout<<"x"<<" ";
						break;
					case finish2:
						cout<<"o"<<" ";
						break;
					case finish3:
						cout<<"x"<<" ";
						break;
					default:
						break;
				}
			}
			cout<<endl;
		}
	}

	void ConnectFourAbstract::createBoard(int r, int c){
		int i,j;
		/*
			Boardun row unu ve column ýný
			set eder.
		*/
		row = r;
		column = c;
		
		gameBoard = new Cell *[r];
		for(i=0;i<r;++i)
			gameBoard[i] = new Cell[c];
			
		for(i=0;i<getRow();++i){                   // Bos Cell lerin hepsinin 
			for(j=0;j<getColumn();++j)             // Cell number ini 0 yapacak.
				gameBoard[i][j].setCellNumber(0);  // Cell dolduruldukca bunlar degisecek.
		}
	}
	
	bool ConnectFourAbstract::boardIsEmpty()const{
		int i;
		for(i=0 ;i<getColumn(); ++i){
			if(columnIsEmpty(i))
				return 1;
		}
		return 0;
	}
	
	bool ConnectFourAbstract::isSimilar(const char str1[16],const char str2[16])const{
		// if two char arrays are equal: return 1 ; else return 0;
		auto ret=1;
		decltype(ret) i ;
		for(i=0;str1[i]!='\0';++i){
			if(str1[i]!=str2[i])
				ret = 0;
		}
		return ret;
	}
	
	void ConnectFourAbstract::changeBoard(whichCell letter, int col){
		int i;
		setLivingCell(1); // 1 pul ekledik.
		for(i=getRow()-1 ;i>=0; --i){
			if(gameBoard[i][col].getWhoCell() == empty ){
				gameBoard[i][col].setWhoCell(letter);
				gameBoard[i][col].setCellNumber(getLivingCell()); // livingCell sayisina gore Cell number ini atadi.
				return;
			}
		}
	}
	
	void ConnectFourAbstract::ifLegal(int & col, char & col_name){
		while(!columnIsEmpty(col)){
			cerr << "FAULT! Enter another one : "<<endl;
			cin >> col_name;
			col_name = toUpperCase(col_name);
			col = convertCharToInt(col_name);
			cin.ignore();
		}
	
		while(!( (col_name>='A' && col_name<='Z') && col<getColumn() )){
			cerr << "FAULT! Enter another one : "<<endl;
			cin >> col_name;
			col_name = toUpperCase(col_name);
			col = convertCharToInt(col_name);
			cin.ignore();
			while(!columnIsEmpty(col)){
				cerr << "FAULT! Enter another one : "<<endl;
				cin >> col_name;
				col_name = toUpperCase(col_name);
				col = convertCharToInt(col_name);
				cin.ignore();
			}
		}
	}
	
	void ConnectFourAbstract::devine(string str, char first[16], char second[16]){
		int i,k;
		for(i=0;i<str.length();++i){
			if(str[i]!=' ')
				first[i] = str[i];
			else{
				first[i] = '\0';
				k = i+1;
				break;	
			}
		}
		i=0;
		while(k<=str.length()){
			if(str[k]!=' ')
				second[i] = str[k];
			else
				second[i] = '\0';
			++i;
			++k;
		}
	}
	
	int ConnectFourAbstract::convertCharToInt(const char c)const{
		int i;
		if(c>='A' && c<='Z')
			i = c-65;  // 65 from ASCII Table
		return i;
	}
	
	bool ConnectFourAbstract::columnIsEmpty(int col)const{
		int i;
		for(i=getRow()-1 ;i>=0; --i){
			if(gameBoard[i][col].getWhoCell() == empty)
				return 1;
		}
		return 0;
	}
	
	char ConnectFourAbstract::toUpperCase(char c)const{
		if(c>='a' && c<='z')
			c = c +'A'-'a';
		return c;
	}
		
	int ConnectFourAbstract::getRow()const{
		return row;
	}
	
	int ConnectFourAbstract::getColumn()const{
		return column;
	}	
	
	//destructor
	ConnectFourAbstract::~ConnectFourAbstract(){
		for(int i=0; i<getRow(); ++i)
			delete [] gameBoard[i];
		delete [] gameBoard;
	}
}// CellSpace
