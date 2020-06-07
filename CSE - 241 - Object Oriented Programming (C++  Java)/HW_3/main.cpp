#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class ConnectFour {
	public:
		inline ConnectFour(){playGame();} // Non-parameter constructor will call playGame Function.
		inline ConnectFour(int newRow, int newCol, char sty):row(newRow),column(newCol),style(sty){}
		inline ConnectFour(int size, char sty):row(size),column(size),style(sty){/* Kare Board yapilmak istenirse. */}
		void playGame(); // Oyun Inputlarinin Alindigi Yer.
		void playMulti();
		void printBoard()const; // Board'u ekrana basar.
		inline void setCell(int nrow, char ncol, char nwhos){Cell(nrow,ncol,nwhos);}
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
		char toUpperCase(char c)const;
		char toLowerCase(char c)const;
		void PvP();
		void PvC();
		void takeMoveVsPC();
		void putPc();
		void save(char name[16])const;
		void load(char name[16]);
		void devine(string str, char first[16], char second[16]);
		void takeMoveVsUsers();
		int convertCharToInt(const char c)const;
		void changeBoard(char letter, int column);
		void ifLegal(int & column, char & col_name);
		bool isSimilar(const char str1[16],const char str2[16])const;
		bool boardIsEmpty()const;
		bool columnIsEmpty(int column)const;
		bool horizonalCheck();
		bool verticalCheck();
		bool diagonalCheck();
		bool totalCheck(); 
		bool compare(const ConnectFour &other)const;
		inline static void setLivingCell(){livingCell += 1;}
		inline static int getLivingCell(){return livingCell;}
		void winningMessage(); // icinde end'i set ettigi icin const degil.
	private:
		class Cell {
			public:
				inline Cell(){
					setRow(0);
					setColumn('A');
					setWhoCell('.');
				}
				inline Cell(int nrow,char col ,char whos){
					setRow(nrow);
					setColumn(col);
					setWhoCell(whos);
				}
				inline Cell(const Cell & other){
					setRow(other.getRow());
					setColumn(other.getColumn());
					setWhoCell(other.getWhoCell());
				}
				inline void set(int newRow,char col ,char whos){setRow(newRow);}
				inline void setRow(int newRow){row = newRow;}
				inline void setColumn(char newCol){column = newCol;}
				inline void setWhoCell(char newWho){whoCell = newWho;}
				inline int getRow()const{return row;}
				inline int getColumn()const{return column;}
				inline char getWhoCell()const{return whoCell;}
			private:
				char column;
				int row;
				char whoCell;
		};
		vector< vector<Cell> > gameCells;
		static int livingCell;
		int row;
		int column;
		char mod; // Simple or Multi.
		char style; // User vs User  or   User vs Computer.
		int turn; // Save Load da sira kimde?
		bool end; // Multi kullanýmda hangi oyunlarýn bittiðini tutacak.
};

int ConnectFour::livingCell = 0;

int main(){
	char mod;
	int game;
	cout << "Enter Game Mod (S for Simple // M for Multi) : ";
	cin >> mod;
	while(mod!='S' && mod!='M'){
		cerr << "Invalid Mod. Enter S / M : ";
		cin >> mod;
	}
	if(mod=='S'){
		ConnectFour gameSimple; // Constructor playGame i calistirir.
		cin.ignore(); // getline da sorun olmamasi icin.
		if(gameSimple.getStyle() == 'P')
			gameSimple.PvP();
		else // it means that style is C.
			gameSimple.PvC();
	}
	else{ // It means that mod is equal to M.
		cout<<"For the First Game"<<endl;
		ConnectFour multi_1;
		cout<<"For the Second Game"<<endl;
		ConnectFour multi_2;
		cout<<"For the Third Game"<<endl;
		ConnectFour multi_3;
		cout<<"For the Fourth Game"<<endl;
		ConnectFour multi_4;
		cout<<"For the Fifth Game"<<endl;
		ConnectFour multi_5;
		
		while(!(multi_1.getEnd()==1 && multi_2.getEnd()==1 && multi_3.getEnd()==1 && multi_4.getEnd()==1 && multi_5.getEnd()==1)){
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

void ConnectFour::playGame(){	
	char style;
	Cell temp;
	vector<Cell> vec;
	int row,col;
	
	cout << "Enter Row Number : ";
	cin >> row;
	while(row<4){
		cerr << "Invalid Row. Enter Bigger than 4. ";
		cin >> row;
	}
	cout << "Enter Column Number : ";
	cin >> col;
	while(col<4 || col >26){ // 26 dan sonra alfadeki tekli harfler bitiyor.
		cerr << "Invalid Column. Enter Bigger than 4, Smaller than 27 : ";
		cin >> col;
	}
	setRow(row);
	setColumn(col);
	cout << "Enter Game Style (P for Player vs Player // C for Player vs Computer) : ";
	cin >> style;
	style = toUpperCase(style);
	while(style!='C' && style!='P'){
		cerr << "Invalid Mod. Enter P / C : ";
		cin >> style;
		style = toUpperCase(style);
	}
	setStyle(style);
	for(int i=0 ;i<getRow(); ++i){
		for(int j=0;j<getColumn();++j){
			temp.setRow(i);
			temp.setColumn(j);
			temp.setWhoCell('.');
			vec.push_back(temp);
		}
		gameCells.push_back(vec);
		vec.clear();
	}
	setEnd(0);
	printBoard();
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

void ConnectFour::PvP(){
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

void ConnectFour::PvC(){
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

void ConnectFour::takeMoveVsUsers(){
	string s1,s2;
	char ld[] = "LOAD";
	char sv[] = "SAVE";
	char col1[16], col2[16];
	int c1,c2;
	if(getTurn()==1 && getStyle() == 'P'){
		cout << "Enter Column for Player 1 or SAVE/LOAD filename : " ; 
		getline(cin,s1); 
		devine(s1,col1,col2);
		if(isSimilar(col1,sv))
			save(col2);           
		else if(isSimilar(col1,ld)){
			load(col2);
		}
		else{
			s1[0] = toUpperCase(s1[0]);
			c1 = convertCharToInt(s1[0]);
			ifLegal(c1,s1[0]);
			changeBoard('X',c1);
			setLivingCell();
			printBoard();	
			setTurn(2);
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
			changeBoard('O',c2);
			setLivingCell();
			printBoard();	
			setTurn(1);
		}		
	}
	while(getStyle() == 'C'&& getMod() =='S'){			//
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
	char sv[] = "SAVE";
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
			changeBoard('O',c1);
			setLivingCell();
			printBoard();	
			setTurn(2);
		}
	}
	
	if(totalCheck() != 1 && getTurn() == 2 && getStyle() == 'C'){
		putPc();
		setLivingCell();
		printBoard();
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

bool ConnectFour::compare(const ConnectFour & other)const{
	if(getLivingCell()<=other.getLivingCell())
		return 1;
	else if(getLivingCell() > other.getLivingCell())
		return 0;
}

void ConnectFour::putPc(){
	int i, j, num;
	if(totalCheck() != 1){
		for(i=getRow()-1 ;i>=0; --i){
			for(j=0 ;j<getColumn(); ++j){
				if(gameCells[i][j].getWhoCell()=='O' && gameCells[i-1][j].getWhoCell()=='.'){
					gameCells[i-1][j].setWhoCell('X');
					printBoard();
					return;
				}
				else if(gameCells[i][j].getWhoCell()=='O'&&gameCells[i][j-1].getWhoCell()=='.'){
					gameCells[i][j-1].setWhoCell('X');
					printBoard();
					return;
				}					
				else if(gameCells[i][j].getWhoCell()=='O'&&gameCells[i][j+1].getWhoCell()=='.'){
					gameCells[i][j].setWhoCell('X');
					printBoard();
					return;
				}					
				else if(gameCells[i][j].getWhoCell()=='O'&&gameCells[i-1][j-1].getWhoCell()=='.'){
					gameCells[i-1][j-1].setWhoCell('X');
					printBoard();
					return;
				}
				else if(gameCells[i][j].getWhoCell()&&gameCells[i-1][j+1].getWhoCell()=='.'){
					gameCells[i-1][j+1].setWhoCell('X');
					printBoard();
					return;
				}	
				else{
					num = rand() % getColumn(); //sütun sayýsýna kadar bir sayý verecek.
					changeBoard('X',num);
					printBoard();
					return;
				}	
			}
		}
	}
}

void ConnectFour::load(char name[16]){
	int i,j;
	char c;
	Cell temp;
	vector<Cell> vec;
	ifstream file;
	file.open(name);
	if(file.fail()){
		cerr << "The Game wasn't Loaded. File NOT FOUND !!!" << endl;
		return;
	}
	
	for(int i=0 ;i<getRow(); ++i){  
		gameCells[i].clear();        //  Eski Tabloyu Sildi.
	}
	
	file >> mod >> turn >> style >> row >> column >> livingCell;
	
	
	
	for(int i=0 ;i<getRow(); ++i){
		for(int j=0;j<getColumn();++j){
			temp.setRow(i);
			temp.setColumn(j);
			temp.setWhoCell('.');
			vec.push_back(temp);
		}
		gameCells.push_back(vec);
		vec.clear();
	}	
	
	for(i=0 ;i<getRow(); ++i){
		for(j=0 ;j<getColumn(); ++j){
			file >> c;
			gameCells[i][j].setWhoCell(c);
		}
	}
	cout << "The Game was Loaded Successfully. The Board is Following. \n";
	
	printBoard();
	
	file.close();
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
	
	file<<getLivingCell()<<endl;    // Living Cell sayýsýný tutar.
	
	for(i=0;i<getRow();++i){            
		for(j=0;j<getColumn();++j)							//  Burada Board ' u txt ye kaydetti.
			file<<gameCells[i][j].getWhoCell()<<" "<<endl;		
	}									

	cout << "The Game was Saved Successfully. "<<endl;

	file.close();
}

bool ConnectFour::isSimilar(const char str1[16],const char str2[16])const{
	auto ret=1;
	decltype(ret) i ;
	for(i=0;str1[i]!='\0';++i){
		if(str1[i]!=str2[i])
			ret = 0;
	}
	return ret;
}

bool ConnectFour::horizonalCheck(){
	int row,col, k;
	char letter,t;
	for(row=getRow()-1 ;row>=0; --row){
		for(col=0 ;col<getColumn(); ++col){	
			if(gameCells[row][col].getWhoCell() != '.'){
				letter = gameCells[row][col].getWhoCell() ;
				if(gameCells[row][col+1].getWhoCell() == letter && gameCells[row][col+2].getWhoCell() == letter && gameCells[row][col+3].getWhoCell() == letter){
					for(k=0;k<4;++k){
						t=toLowerCase(gameCells[row][col+k].getWhoCell());	
						gameCells[row][col+k].setWhoCell(t);
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
	char letter,t;
	for(col=0 ;col<getColumn(); ++col){
		for(row=getRow()-1 ;row>0; --row){	
			if(gameCells[row][col].getWhoCell() != '.' ){
				letter = gameCells[row][col].getWhoCell() ;
				if(gameCells[row-1][col].getWhoCell() == letter && gameCells[row-2][col].getWhoCell() == letter && gameCells[row-3][col].getWhoCell() == letter){
					for(k=0;k<4;++k){
						t=toLowerCase(gameCells[row-k][col].getWhoCell());
						gameCells[row-k][col].setWhoCell(t);
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
	char letter,t;
	for(row=getRow()-1 ;row>0; --row){
		for(col=0 ;col<getColumn(); ++col){
			if(gameCells[row][col].getWhoCell() != '.'){
				letter = gameCells[row][col].getWhoCell() ;
				if(gameCells[row-1][col+1].getWhoCell() == letter && gameCells[row-2][col+2].getWhoCell() == letter && gameCells[row-3][col+3].getWhoCell() == letter){
					for(k=0;k<4;++k){
						t=toLowerCase(gameCells[row-k][col+k].getWhoCell());	
						gameCells[row-k][col+k].setWhoCell(t);
					}
					return 1;
				}
				else if(gameCells[row-1][col-1].getWhoCell() == letter && gameCells[row-2][col-2].getWhoCell() == letter && gameCells[row-3][col-3].getWhoCell() == letter){
					for(k=0;k<4;++k){
						t=toLowerCase(gameCells[row-k][col-k].getWhoCell());
						gameCells[row-k][col-k].setWhoCell(t);	
					}
					return 1;
				}
			}
		}
	}
	return 0;
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


void ConnectFour::changeBoard(char letter, int column){
	int i;
	for(i=getRow()-1 ;i>=0; --i){
		if(gameCells[i][column].getWhoCell() == '.' ){
			gameCells[i][column].setWhoCell(letter);
			break;
		}
	}
}

bool ConnectFour::totalCheck(){
	// Const olmamasinin nedeni icindeki check fonksiyonlarinin kazanma durumunda icindeki harfleri kucuk harfe donusturmesi. 
	// Bu nedenle horizonal-vertical-diagonal checkler const degil.
	return(horizonalCheck() || verticalCheck() || diagonalCheck());
}


void ConnectFour::winningMessage(){
	int i, j;
	char c;
	printBoard();
	for(i=0 ;i<getRow(); ++i){
		for(j=0 ;j<getColumn(); ++j){
			if(gameCells[i][j].getWhoCell() >= 'a' && gameCells[i][j].getWhoCell()<='z'){
				c = gameCells[i][j].getWhoCell();
				break;
			}
		}
	}
	if(c=='x')
		cout << "Player 1 Win This Game ... " <<endl;
	else if(c=='o')
		cout << "Player 2 Win This Game ... " <<endl;
		
	setEnd(1);
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

bool ConnectFour::columnIsEmpty(int column)const{
	int i;
	for(i=getRow()-1 ;i>=0; --i){
		if(gameCells[i][column].getWhoCell() == '.')
			return 1;
	}
	return 0;
}

void ConnectFour::printBoard()const{
	int i,j;
	char k = 'a';
	cout<< "Living Cell is : " <<getLivingCell()<<endl;
	for(i=0 ;i<getColumn(); ++i, ++k)
		cout << k << " ";
	cout << endl;	
	for(i=0 ;i<getRow(); ++i){
		for(j=0;j<getColumn();++j){
			cout<< gameCells[i][j].getWhoCell() <<" ";
		}
		cout<<endl;
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

char ConnectFour::toLowerCase(char c)const{
	if(c>='A' && c<='Z')
		c = c +'a'-'A';
	return c;
}
