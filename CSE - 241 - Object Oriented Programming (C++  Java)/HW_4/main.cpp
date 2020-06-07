/*
	YAGIZ DONER -- 141044062 -- CSE241 -- HW-4 --
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Random Sayý Alabilmek Ýçin

using namespace std;

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

class ConnectFour {
	public:
		ConnectFour(){createBoard(5,5);} // non-parameter constructor is calling a 5*5 sizes board.
		ConnectFour(int r, int c){createBoard(r,c);} // According to parameters, create a board.
		ConnectFour(string name){board(name);} // According to the text files, create a board.
		void play();
		void play(int ignore);
		void takeMoveVsUsers();
		void takeMoveVsPC();
		void board(string name);
		void putPc();
		void playGame();
		void playMulti();
		bool horizonalCheck();
		bool verticalCheck();
		bool diagonalCheck();
		bool totalCheck(); 
		bool isSimilar(const char str1[16],const char str2[16])const;
		void changeBoard(whichCell letter, int column);
		void ifLegal(int & column, char & col_name);
		void devine(string str, char first[16], char second[16]);
		int convertCharToInt(const char c)const;
		bool boardIsEmpty()const;
		bool columnIsEmpty(int column)const;	
		char toUpperCase(char c)const;
		void createBoard(int row, int column);
		void printBoard()const;
		friend bool operator ==(const ConnectFour & o1, const ConnectFour & o2);
		friend bool operator !=(const ConnectFour & o1, const ConnectFour & o2);
		inline void setCell(int nrow, char ncol, whichCell nwhos){Cell(nrow,ncol,nwhos);}
		inline void setRow(int newRow){row = newRow;}
		inline void setColumn(int newCol){column = newCol;}
		inline int getRow()const{return row;}
		inline int getColumn()const{return column;}
		inline char getMod()const{return mod;}
		inline char getStyle()const{return style;}
		inline void setMod(char newMod){mod = newMod;}
		inline void setStyle(char newStyle){style = newStyle;}
		inline void setTurn(int newTurn){turn = newTurn;}
		inline int getTurn()const{return turn;}
		inline bool getEnd()const{return end;}
		inline void setEnd(bool newEnd){end=newEnd;}
		void save(char name[16])const;
		void load(char name[16]);
		void winningMessage(); // icinde end'i set ettigi icin const degil.
		~ConnectFour();
	private:
		class Cell {
			public:				
				// when someone win the game. Its cell return to finish1(for user1), finish2(for user2) or finish3(for computer). 
				inline Cell(){
					setRow(0);
					setColumn('A');
					setWhoCell(empty);
				}
				inline Cell(int nrow,char col ,whichCell whos){
					setRow(nrow);
					setColumn(col);
					setWhoCell(whos);
				}
				inline Cell(const Cell & other){
					setRow(other.getRow());
					setColumn(other.getColumn());
					setWhoCell(other.getWhoCell());
				}
				const bool operator ==(const Cell & other)const{
					return(whoCell == other.getWhoCell());
				}
				Cell operator ++(){ // for pre. increment.
					switch(whoCell){
						case empty:
								setWhoCell(user1);
								break;
						case user1:
								setWhoCell(user2);
								break;
						case user2:
								setWhoCell(computer);
								break;
						case computer:
								setWhoCell(empty);
								break;
						default: break;
					}
					return Cell(row,column,whoCell);
				}
				Cell operator ++(int ignore){ // for post. increment.
					whichCell temp = whoCell;
					switch(whoCell){
						case empty:
								setWhoCell(user1);
								break;
						case user1:
								setWhoCell(user2);
								break;
						case user2:
								setWhoCell(computer);
								break;
						case computer:
								setWhoCell(empty);
								break;
						default: break;
					}
					return Cell(row,column,temp);
				}
				friend ostream& operator << (ostream& out, const Cell& object ){
					out<< "Row is "<<object.getRow()<<endl;
					out<< "Column is "<<object.getColumn()<<endl;
					out<< "Cell is "<<object.getWhoCell()<<endl;
					return out;
				}
				friend istream& operator >> (istream& in, Cell& object){
					int row;
					char column;
					in >> row >> column;
					object.setRow(row);
					object.setColumn(column);
					return in;
				}
				inline void setRow(int newRow){row = newRow;}
				inline void setColumn(char newCol){column = newCol;}
				inline void setWhoCell(whichCell newCell){whoCell = newCell;}
				inline int getRow()const{return row;}
				inline int getColumn()const{return column;}
				inline whichCell getWhoCell()const{return whoCell;}
			private:
				char column;
				int row;
				whichCell whoCell;
		};
		Cell ** gameBoard;
		int row;
		int column;
		char mod; // Simple or Multi.
		char style; // User vs User  or   User vs Computer.
		int turn; // Save Load da sira kimde?
		bool end; // Multi kullanýmda hangi oyunlarýn bittiðini tutacak.
};

int main (){
	int game;
	char mod;
	// Oyun modunu alacak.
	cout << "Enter Game Mod (S for Simple // M for Multi) : ";
	cin >> mod;
	while(mod!='S' && mod!='M'){
		cerr << "Invalid Mod. Enter S / M : ";
		cin >> mod;
	}
	
	/*
		This Block is for a Simple Game.
	*/
	if(mod=='S'){
		ConnectFour gameSimple; // Creat a 5x5 game.
		gameSimple.playGame(); // In here, Board is chancing according to txt.
		cin.ignore(); // getline da sorun olmamasi icin.
		if(gameSimple.getStyle() == 'P')
			gameSimple.play(1); // 1 burada ignore edilir. Sadece o fonksiyonu cagirmak icin.
		else // it means that style is C.
			gameSimple.play();
	}
	
	/*
		This Block is for Multi Games.
	*/
	else{ // It means that mod is equal to M.
		ConnectFour multi_1, multi_2, multi_3, multi_4, multi_5;
		
		multi_1.playGame();
		multi_2.playGame();
		multi_3.playGame();
		multi_4.playGame();
		multi_5.playGame();
		
		while(!(multi_1.getEnd()==1 && multi_2.getEnd()==1 && multi_3.getEnd()==1 && multi_4.getEnd()==1 && multi_5.getEnd()==1)){
			// Oyunlarýn hepsi bitmedigi surece bu while devam edecek.
			cout << "Which Game Do You Want to Play (1 to 5) : ";
			cin >> game;	
			while(game<1 || game >5){
				cerr << "Fault. Enter 1 to 5 : ";
				cin >> game;
			}
			cin.ignore(); // getline da sorun yasamamak icin.
			switch(game){
				case 1: if(multi_1.getEnd()!=1){
							multi_1.printBoard();
							multi_1.playMulti();
						}
						else
							cerr<<"This Game was End."<<endl;
						break;
				case 2: if(multi_2.getEnd()!=1){
							multi_2.printBoard();
							multi_2.playMulti();
						}
						else
							cerr<<"This Game was End."<<endl;
						break;
				case 3: if(multi_3.getEnd()!=1){
							multi_3.printBoard();
							multi_3.playMulti();
						}
						else
							cerr<<"This Game was End."<<endl;
						break;
				case 4: if(multi_4.getEnd()!=1){
							multi_4.printBoard();
							multi_4.playMulti();
						}
						else
							cerr<<"This Game was End."<<endl;
						break;
				case 5: if(multi_5.getEnd()!=1){
							multi_5.printBoard();
							multi_5.playMulti();
						}
						else
							cerr<<"This Game was End."<<endl;
						break;
			}
		}	
		cout << "The Games were End...";	
	}
	return 0;
}

bool operator ==(const ConnectFour & o1, const ConnectFour & o2){
	int i,j;
	//eger row veya column farklýysa direk 0 return eder 
	if( o1.getRow() != o2.getRow() || o1.getColumn() != o2.getColumn() )
		return 0;
	//eger col ve row aynýysa elemanlarýna bakar
	for(i=0;i<o1.getRow();++i){
		for(j=0;j<o1.getColumn();++j){
			if(o1.gameBoard[i][j].getWhoCell() != o2.gameBoard[i][j].getWhoCell())
				return 0; // ayný olmayan bir eleman gordugunde sýfýr doner
		}
	}
	return 1;
}

/*
	operator == tam tersi olacagi icin bu fonksiyonda 
	operator == ' i kullandým.
*/
bool operator !=(const ConnectFour & o1, const ConnectFour & o2){
	return(! (o1==o2));
}

/*
	Kullanýcýdan gelen txt ye gore board olusacak.
*/
void ConnectFour::board(string name){
	ifstream file;
	file.open(name);
	string line;
	int i,c,r=0,j;
	if(file.fail()){
		cerr << "The Game wasn't Loaded. File NOT FOUND !!!" << endl;
		return;
	}
	while(getline(file,line)){
		/* Find the row number in the file. (variable r)*/
		r++;
		c=line.length();
		/* Find the column number in the file. (variable c) */
	}
	
	/*
		According to row and column. Create an Empty Board.
	*/
	createBoard(r,c);
	
	/*
		return to beginnig of the file.
	*/
    file.clear(); 
	file.seekg(0);
	
	/*
		Dosyaya gore boardumuzu nokta veya bos 
		sekilde dolduracak.
	*/
	for(i=0 ;i<r; ++i){
		getline(file,line,'\n');
		for(j=0 ;j<c; ++j){
			if(line[j] == ' ')
				gameBoard[i][j].setWhoCell(unused);
			else if(line[j] == '*')
				gameBoard[i][j].setWhoCell(empty);		
		}
	}
	file.close();
}

//destructor
ConnectFour::~ConnectFour(){
	for(int i=0; i<getRow(); ++i)
		delete [] gameBoard[i];
	delete [] gameBoard;
}

void ConnectFour::createBoard(int r, int c){
	int i,j;
	/*
		Boardun row unu ve column ýný
		set eder.
	*/
	setRow(r);
	setColumn(c);
	
	gameBoard = new Cell *[r];
	for(i=0;i<r;++i)
		gameBoard[i] = new Cell[c];
}

void ConnectFour::playGame(){	
	cin.ignore();//getline da sorun yasamamak icin.
	string name;
	cout<<"Enter the Game Board File Name : ";
	getline(cin,name);
	board(name);
	
	// oyun stilini alýr.
	char style;
	cout << "Enter Game Style (P for Player vs Player // C for Player vs Computer) : ";
	cin >> style;
	style = toUpperCase(style);
	while(style!='C' && style!='P'){
		cerr << "Invalid Mod. Enter P / C : ";
		cin >> style;
		style = toUpperCase(style);
	}
	
	setStyle(style); // oyun stilini set eder.
	setEnd(0); // oyunlarýn bitmediðini set eder.
	printBoard();
}

void ConnectFour::play(){ // play Simple - versusComuter.
	setTurn(1);
	setStyle('C');   

    do{
    	if(boardIsEmpty())
    		takeMoveVsPC();
    	else{
    		cout << "Nobody Win This Game."<<endl;
    		break;
		}
	}while(totalCheck() != 1);
	
	winningMessage();
}

void ConnectFour::play(int ignore){ // play Simple - versusPlayers.
	setTurn(1);
	setStyle('P');
	do{
		if(boardIsEmpty())
			takeMoveVsUsers();
		else{
			cout << "Nobody Win This Game." << endl;
			break;
		}
	}while(totalCheck() != 1);
	
	winningMessage();
}

void ConnectFour::playMulti(){
	setTurn(1);
	if(getStyle() == 'P'){
		if(boardIsEmpty())
			takeMoveVsUsers();
		else{
			cout << "Nobody Win This Game." << endl;
			setEnd(1);
		}
		if(totalCheck()==1)
			winningMessage();
	}
	else{ // it means that style is equal to C.
		if(boardIsEmpty())
    		takeMoveVsPC();
    	else{
			cout << "Nobody Win This Game." << endl;
			setEnd(1);
		}
		if(totalCheck()==1)
			winningMessage();
	}
}

void ConnectFour::takeMoveVsUsers(){
	string s1,s2;
	char ld[] = "LOAD";
	char sv[] = "SAVE";
	char col1[16], col2[16];
	int c1,c2;
	if(getTurn()==1 && getStyle() == 'P'){
		cout << "Enter Column for Player 1 or SAVE/LOAD filename : " ; 
		getline(cin,s1); // girdiði  degeri stringe alýr.
		devine(s1,col1,col2); // save ve load ý anlamak icin bu fonk. kullanýlýr.
		// col1 e save veya load varsa atanýr. col2 ye hangi txt dosyasý oldugu.
		if(isSimilar(col1,sv))
			save(col2);	
		else if(isSimilar(col1,ld))
			load(col2);
		else{
			//eger save-load yoksa gerekli islemleri yapar ve board a pulu ekler.
			s1[0] = toUpperCase(s1[0]);
			c1 = convertCharToInt(s1[0]);
			ifLegal(c1,s1[0]);
			changeBoard(user1,c1);
			printBoard();	
			setTurn(2); // sýrayý ikinci oyuncuya býrakir.
		}
	}
	
	if(totalCheck() != 1 && getTurn() == 2 && getStyle() == 'P'){
		cout << "Enter Column for Player 2 or SAVE/LOAD filename : " ;
		getline(cin,s2);
		devine(s2,col1,col2);
		if(isSimilar(col1,sv))
			save(col2);
		else if(isSimilar(col1,ld))
			load(col2);
		else{
			s2[0] = toUpperCase(s2[0]);
			c2 = convertCharToInt(s2[0]);			
			ifLegal(c2,s2[0]);		
			changeBoard(user2,c2);
			printBoard();	
			setTurn(1);
		}		
	}
	while(getStyle() == 'C' && getMod() =='S'){			//
		if(boardIsEmpty() && totalCheck() != 1)   		//
			takeMoveVsPC();   							//  Bu blok Sadece Player ile oynarken
		else{										    //  LOAD dan Bilgisayara karþý oynanan
    		cout << "Nobody Win This Game."<< endl; 	//	oyuna geçer ise çalýþacak... 
    		break;										//
		}												//
	}
}

void ConnectFour::takeMoveVsPC(){
	string s1;
	char ld[] = "LOAD";
	char sv[]= "SAVE";
	char col1[16], col2[16];
	int c1;
	
	if(getTurn()==1 && getStyle()=='C'){
		cout << "Enter Column for Player or SAVE/LOAD filename : "<<endl ;
		getline(cin,s1);
		devine(s1,col1,col2);
		if(isSimilar(col1,sv))
			save(col2);
		else if(isSimilar(col1,ld))
			load(col2);
		else{
			s1[0] = toUpperCase(s1[0]);
			c1 = convertCharToInt(s1[0]);
			ifLegal(c1,s1[0]);
			changeBoard(user2,c1);
			printBoard();	
			setTurn(2);
		}
	}
	
	if(totalCheck() != 1 && getTurn() == 2 && getStyle() == 'C'){
		putPc();
		setTurn(1) ;	
	}
	
	while(getStyle()=='P' && getMod()=='S'){                        //  Sadece simple gamede
		if(boardIsEmpty() && totalCheck() != 1)                     //  gecerli olmak uzere;
			takeMoveVsUsers(); 									    //  Bu blok Sadece Bilgisayar ile oynarken
		else{													    //  LOAD dan Playera karþý oynanan
    		cout << "Nobody Win This Game."<<endl;  				//	oyuna geçer ise çalýþacak... 
    		break;													//	
		}															//
	}
}

void ConnectFour::save(char name[16])const{
	int i,j;
	ofstream file;
	file.open(name);
	if(file.fail()){
		cerr << "The Game wasn't Saved. File NOT OPENED !!!" << endl;
		return;
	}
	file<<getMod()<<endl;  // oyun modunu tutar.
	
	file<<getTurn()<<endl;							// Kimin sýrasý olduðunu kaydetti.
	
	file<<getStyle()<<endl;                    //  Burada oyun tipini txt'ye kaydetti.
	
	file<<getRow()<<endl;  					// Burada satýr sayýsýný txt ye kaydetti.
	
	file<<getColumn()<<endl;               // Burada sütun sayýsýný txt ye kaydetti.
	
	for(i=0;i<getRow();++i){            
		for(j=0;j<getColumn();++j)							//  Burada Board ' u txt ye kaydetti.
			file<<gameBoard[i][j].getWhoCell()<<endl;		
	}									

	cout << "The Game was Saved Successfully. "<<endl;

	file.close();
}

void ConnectFour::load(char name[16]){
	int i,j,k;
	ifstream file;
	file.open(name);
	if(file.fail()){
		cerr << "The Game wasn't Loaded. File NOT FOUND !!!" << endl;
		return;
	}
	
	for(int i=0 ;i<getRow(); ++i) 
		delete [] gameBoard[i] ;      //  Eski Tabloyu Sildi.
	delete [] gameBoard;
	
	file >> mod >> turn >> style >> row >> column ;
	
	
	createBoard(row,column); // bos bir board yapar.
		
	/*
		board u enum type a gore doldurur.
	*/
	for(i=0 ;i<getRow(); ++i){
		for(j=0 ;j<getColumn(); ++j){
			file >> k;
			switch(k){
				case 0: 
					gameBoard[i][j].setWhoCell(empty);
					break;
				case 1:
					gameBoard[i][j].setWhoCell(user1);
					break;
				case 2:
					gameBoard[i][j].setWhoCell(user2);
					break;
				case 3:
					gameBoard[i][j].setWhoCell(computer);
					break;
				case 4:
					gameBoard[i][j].setWhoCell(finish1);
					break;
				case 5:
					gameBoard[i][j].setWhoCell(finish2);
					break;
				case 6:
					gameBoard[i][j].setWhoCell(finish3);
					break;
				case 7:
					gameBoard[i][j].setWhoCell(unused);
					break;
				default:
					break;
			}
		}
	}
	cout << "The Game was Loaded Successfully. The Board is Following. \n";
	
	printBoard();
	
	file.close();
}


/*
	Computer a karsi durumda Computer in hamlelerini
	yapan fonksiyon fakat 
	Hw 1-2-3 'e gore daha guclendirdim.
*/
void ConnectFour::putPc(){
	int i, j, num;
	if(totalCheck() != 1){
		
		/*
			Eger kazanma durumu varsa kazanacak.
		*/
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j].getWhoCell()==computer && gameBoard[i-2][j].getWhoCell()==computer && gameBoard[i-3][j].getWhoCell()==empty){
					changeBoard(computer,j);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j+1].getWhoCell()==computer && gameBoard[i][j+2].getWhoCell()==computer && gameBoard[i][j+3].getWhoCell()==empty){
					changeBoard(computer,j+3);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j-1].getWhoCell()==computer && gameBoard[i][j-2].getWhoCell()==computer && gameBoard[i][j-3].getWhoCell()==empty){
					changeBoard(computer,j-3);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j+1].getWhoCell()==computer && gameBoard[i-2][j+2].getWhoCell()==computer && gameBoard[i-3][j+3].getWhoCell()==empty){
					changeBoard(computer,j+3);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j-1].getWhoCell()==computer && gameBoard[i-2][j-2].getWhoCell()==computer && gameBoard[i-3][j-3].getWhoCell()==empty){
					changeBoard(computer,j-3);
					printBoard();
					return;
				}
			}
		}
		
		/*
			Eger kaybetme durumu varsa kaybetmemeye calýsacak.
		*/
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j].getWhoCell()==user2 && gameBoard[i-2][j].getWhoCell()==user2 && gameBoard[i-3][j].getWhoCell()==empty){
					changeBoard(computer,j);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j+1].getWhoCell()==user2 && gameBoard[i][j+2].getWhoCell()==user2 && gameBoard[i][j+3].getWhoCell()==empty){
					changeBoard(computer,j+3);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j-1].getWhoCell()==user2 && gameBoard[i][j-2].getWhoCell()==user2 && gameBoard[i][j-3].getWhoCell()==empty){
					changeBoard(computer,j-3);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j+1].getWhoCell()==user2 && gameBoard[i-2][j+2].getWhoCell()==user2 && gameBoard[i-3][j+3].getWhoCell()==empty){
					changeBoard(computer,j+3);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j-1].getWhoCell()==user2 && gameBoard[i-2][j-2].getWhoCell()==user2 && gameBoard[i-3][j-3].getWhoCell()==empty){
					changeBoard(computer,j-3);
					printBoard();
					return;
				}
			}
		}
		
		/*
			Usttekiler Saglamazsa ikili durumlar devreye girecek. Once Savunacak, Savunamaz ise saldýracak.
		*/
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j].getWhoCell()==user2 && gameBoard[i-2][j].getWhoCell()==empty){
					changeBoard(computer,j);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j+1].getWhoCell()==user2 && gameBoard[i][j+2].getWhoCell()==empty){
					changeBoard(computer,j+2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j-1].getWhoCell()==user2 && gameBoard[i][j-2].getWhoCell()==empty){
					changeBoard(computer,j-2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j+1].getWhoCell()==user2 && gameBoard[i-2][j+2].getWhoCell()==empty){
					changeBoard(computer,j+2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j-1].getWhoCell()==user2 && gameBoard[i-2][j-2].getWhoCell()==empty){
					changeBoard(computer,j-2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j].getWhoCell()==computer && gameBoard[i-2][j].getWhoCell()==empty){
					changeBoard(computer,j);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j+1].getWhoCell()==computer&& gameBoard[i][j+2].getWhoCell()==empty){
					changeBoard(computer,j+2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i][j-1].getWhoCell()==computer&& gameBoard[i][j-2].getWhoCell()==empty){
					changeBoard(computer,j-2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j+1].getWhoCell()==computer && gameBoard[i-2][j+2].getWhoCell()==empty){
					changeBoard(computer,j+2);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==computer && gameBoard[i-1][j-1].getWhoCell()==computer && gameBoard[i-2][j-2].getWhoCell()==empty){
					changeBoard(computer,j-2);
					printBoard();
					return;
				}
			}
		}
		
		/*
			Tekli durumlar en son ihtimalde calisacak.
		*/
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0 ;j<getColumn(); ++j){
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j].getWhoCell()==empty){
					changeBoard(computer,j);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i][j-1].getWhoCell()==empty){
					changeBoard(computer,j-1);
					printBoard();
					return;
				}					
				if(gameBoard[i][j].getWhoCell()==user2 &&gameBoard[i][j+1].getWhoCell()==empty){
					changeBoard(computer,j+1);
					printBoard();
					return;
				}					
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j-1].getWhoCell()==empty){
					changeBoard(computer,j-1);
					printBoard();
					return;
				}
				if(gameBoard[i][j].getWhoCell()==user2 && gameBoard[i-1][j+1].getWhoCell()==empty){
					changeBoard(computer,j+1);
					printBoard();
					return;
				}	
				/*
					Hicbir durum olmaz ise random atama yapacak.
				*/
				else{
					num = rand() % getColumn(); //sütun sayýsýna kadar bir sayý verecek.
					changeBoard(computer,num);
					printBoard();
					return;
				}	
			}
		}
	}
}

bool ConnectFour::isSimilar(const char str1[16],const char str2[16])const{
	// if two char arrays are equal: return 1 ; else return 0;
	auto ret=1;
	decltype(ret) i ;
	for(i=0;str1[i]!='\0';++i){
		if(str1[i]!=str2[i])
			ret = 0;
	}
	return ret;
}

bool ConnectFour::totalCheck(){
	// Const olmamasinin nedeni icindeki check fonksiyonlarinin kazanma 
	// durumunda icindeki enum tipi finishlere donusturmesi. 
	// Bu nedenle horizonal-vertical-diagonal checkler const degil.
	return(horizonalCheck() || verticalCheck() || diagonalCheck());
}

bool ConnectFour::horizonalCheck(){
	int row,col, k;
	whichCell letter;
	for(row=getRow()-1 ;row>=0; --row){
		for(col=0 ;col<getColumn(); ++col){	
			if(gameBoard[row][col].getWhoCell() != empty && gameBoard[row][col].getWhoCell() != unused){
				letter = gameBoard[row][col].getWhoCell() ;
				if(gameBoard[row][col+1].getWhoCell() == letter && gameBoard[row][col+2].getWhoCell() == letter && gameBoard[row][col+3].getWhoCell() == letter){
					if(letter == user1){
						for(k=0;k<4;++k)
							gameBoard[row][col+k].setWhoCell(finish1);	
					}
					else if(letter == user2){
						for(k=0;k<4;++k)
							gameBoard[row][col+k].setWhoCell(finish2);	
					}
					else if(letter == computer){
						for(k=0;k<4;++k)
							gameBoard[row][col+k].setWhoCell(finish3);	
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

bool ConnectFour::verticalCheck(){
	int row,col,k;
	whichCell letter;
	for(col=0 ;col<getColumn(); ++col){
		for(row=getRow()-1 ;row>0; --row){	
			if(gameBoard[row][col].getWhoCell() != empty && gameBoard[row][col].getWhoCell() != unused){
				letter = gameBoard[row][col].getWhoCell() ;
				if(gameBoard[row-1][col].getWhoCell() == letter && gameBoard[row-2][col].getWhoCell() == letter && gameBoard[row-3][col].getWhoCell() == letter){
					if(letter == user1){
						for(k=0;k<4;++k)
							gameBoard[row-k][col].setWhoCell(finish1);	
					}
					else if(letter == user2){
						for(k=0;k<4;++k)
							gameBoard[row-k][col].setWhoCell(finish2);	
					}
					else if(letter == computer){
						for(k=0;k<4;++k)
							gameBoard[row-k][col].setWhoCell(finish3);	
					}
					return 1;					
				}
			}
		}
	}
	return 0;
}

bool ConnectFour::diagonalCheck(){
	int row,col,k;
	whichCell letter;
	for(row=getRow()-1 ;row>0; --row){
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

void ConnectFour::winningMessage(){
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
	setEnd(1);
}

void ConnectFour::changeBoard(whichCell letter, int column){
	int i;
	for(i=getRow()-1 ;i>=0; --i){
		if(gameBoard[i][column].getWhoCell() == empty ){
			gameBoard[i][column].setWhoCell(letter);
			break;
		}
	}
}

void ConnectFour::printBoard()const{
	int i,j;
	char k = 'a';
	for(i=0 ;i<getColumn(); ++i, ++k)
		cout << k << " ";
	cout << endl;	
	for(i=0 ;i<getRow(); ++i){
		for(j=0;j<getColumn();++j){
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

void ConnectFour::ifLegal(int & column, char & col_name){
	
	while(!columnIsEmpty(column)){
		cerr << "FAULT! Enter another one : "<<endl;
		cin >> col_name;
		col_name = toUpperCase(col_name);
		column = convertCharToInt(col_name);
		cin.ignore();
	}
	
	while(!( (col_name>='A' && col_name<='Z') && column<getColumn() )){
		cerr << "FAULT! Enter another one : "<<endl;
		cin >> col_name;
		col_name = toUpperCase(col_name);
		column = convertCharToInt(col_name);
		cin.ignore();
		while(!columnIsEmpty(column)){
			cerr << "FAULT! Enter another one : "<<endl;
			cin >> col_name;
			col_name = toUpperCase(col_name);
			column = convertCharToInt(col_name);
			cin.ignore();
		}
		
	}
}

bool ConnectFour::columnIsEmpty(int column)const{
	int i;
	for(i=getRow()-1 ;i>=0; --i){
		if(gameBoard[i][column].getWhoCell() == empty)
			return 1;
	}
	return 0;
}

bool ConnectFour::boardIsEmpty()const{
	int i;
	for(i=0 ;i<getColumn(); ++i){
		if(columnIsEmpty(i))
			return 1;
	}
	return 0;
}

void ConnectFour::devine(string str, char first[16], char second[16]){
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

int ConnectFour::convertCharToInt(const char c)const{
	int i;
	if(c>='A' && c<='Z')
		i = c-65;  // 65 from ASCII Table
	return i;
}

char ConnectFour::toUpperCase(char c)const{
	if(c>='a' && c<='z')
		c = c +'A'-'a';
	return c;
}
