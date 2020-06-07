#include <iostream>
#include <fstream>
#include <cstdlib> // Random sayi alabilmek icin
using namespace std;

void makeBoard(char board[20][20], int size);//Board'u istenilen size'a göre olusturacak.
void printBoard(char board[20][20], int size);// Board'u ekrana basacak.
void changeBoard(char board[20][20], const char letter, int column, int size);//Input a göre board'u degistirecek.
void takeMoveVsUsers(char board[20][20], const char letter1,const char letter2, int size, char game, int & turn);// 2 Kullanicidan da hareketlerin alinip islenecegi yer.
void takeMoveVsPC(char board[20][20], const char letter1,const char letter2, int size,char game, int & turn);// Kullanıcı ve PC hareketlerinin alinip islenecegi yer.
int horizonalCheck(char board[20][20], int size); // yatay kontrolü yapacak.
int verticalCheck(char board[20][20], int size); // dikey kontrolü yapacak.
int diagonalCheck(char board[20][20], int size); // capraz kontrolü yapacak.
int totalCheck(char board[20][20], int size); // yatay, dikey ve çapraz olarak 4'lülügü kontrol edecek ve 4'lü varsa 1 yoksa 0 return edecek.
void versusUsers(char board[20][20], int size, char game); // Ýki kullanýcý arasýndaki oyunu baþlatacak.
void versusComputer(char board[20][20], int size, char game); // Bilgisayar ve Kullanici arasindaki Oyunu Baslatacak.
void putPC(char board[20][20], int size); //  Bilgisayarýn Otomatik Hareketlerini Gerçeklestirecek.
int convertCharToInt(const char c); // girilen harfin array de tam sayi alarak kullanilabilmesi için ...
bool columnIsEmpty(char board[20][20],int size, int column);  // if return 1 : column is empty, return 0 : column is full.
void ifLegal(char board[20][20], int size, int & column, char & col_name); // Girilen girdinin board'a uygunluðuna bakilip duruma göre yeniden girdi istenilecek.
bool boardIsEmpty(char board[20][20], int size); // if return 1 : board is empty, return 0 : board is full.
void toUpperCase(char & c); // lower case to Upper case.
void toLowerCase(char & c); // upper case to Lower case.
void winningMessage(char board[20][20], int size); // Galibiyet Durumununa göre sonucu ekrana basacak.
/*
	Buradan Sonraki Fonksiyonlar HW-2 de kullanilmistir... Yukardaki Bazı fonksiyonlar ihtiyaca gore guncellenmistir.
*/
bool isSimilar(char str1[16],char str2[16]);  // str1 and str2 is equal or not. if egual return 1, else return 0.
void devine(char str[25], char first[10], char second[20]); // ilk verilen karakter arrayini ortadaki space a gore bolup diger iki array a verecek...
void load (char board[20][20],int & size, char & game, int & turn, char name[16]); // Load the Game
void save(char board[20][20], int size, char game, int turn, char name[16]); // Save the Game

int main(){
	int size;
	char game;
	
	cout << "Enter the Board Size (The Board size can be 4x4,6x6 , ... , 20x20) : " ;
	cin >> size;
	
	while(!(size>=4 && size<=20 && size%2 == 0)){  // Validity of Board Size
		cerr << "Please Enter a Number depending on the Rule : ";
		cin >> size;
	}
	
	cout << "Which game do you Want to Play ? \n Enter P for versus Players. \n Enter C for versus Computer. \n : ";
	cin >> game;
	toUpperCase(game);	
	while(!(game=='C' || game=='P')){     // Validity of Game Style
		cerr << "Enter P or C...";
		cin >> game;
		toUpperCase(game);
	}
	
	cin.ignore(); // daha sonrasinda getline de sikinti yasamamak icin buffer'ı bosaltir.
	char board[20][20];
	
	if(game == 'P')
		versusUsers(board, size,game);
	else // Game C 'den baska bir sey olamayacagi için bosa kontrol yapmayacak.
		versusComputer(board, size,game);
	
	return 0;
}

void load (char board[20][20],int & size, char & game, int & turn, char name[16]){
	int i,j;
	ifstream file;
	file.open(name);
	if(file.fail()){
		cerr << "The Game wasn't Loaded. File NOT FOUND !!!" << endl;
		return;
	}
	file >> turn >> game >> size ;

	for(i=0 ;i<size; ++i){
		for(j=0 ;j<size; ++j)
			file >> board[i][j];
	}
	cout << "The Game was Loaded Successfully. The Board is Above. \n";
	printBoard(board,size);
	file.close();
}

void save(char board[20][20],int size, char game, int turn, char name[16]){
	int i,j;
	ofstream file;
	file.open(name);
	if(file.fail()){
		cerr << "The Game wasn't Saved. File NOT OPENED !!!" << endl;
		return;
	}
	file<<turn<<endl;							// Kimin sýrasý olduðunu kaydetti.
	
	file<<game<<" "<<endl;                    //  Burada oyun tipini txt'ye kaydetti.
	
	file<<size<<" "<<endl;  					// Burada size'ý txt ye kaydetti.
	
	for(i=0;i<size;++i){                //
		for(j=0;j<size;++j)				//  Burada Board ' u txt ye kaydetti.
			file<<board[i][j]<<" "<<endl;		//  
	}									

	cout << "The Game was Saved Successfully. "<<endl;

	file.close();
}

void versusUsers(char board[20][20], int size, char game){
	char letter1 = 'X', letter2 = 'O';
	int turn=1;
	makeBoard(board,size);
	printBoard(board,size);   
	 
    	do{
	    	if(boardIsEmpty(board,size))
	    		takeMoveVsUsers(board,letter1,letter2,size,game,turn);
	    	else{
	    		cout << "Nobody Win This Game." << endl;
	    		break;
		}
	}while(totalCheck(board,size) != 1);
	
	winningMessage(board,size);
}

void takeMoveVsUsers(char board[20][20], const char letter1,const char letter2, int size,char game, int & turn){
	char col1[16],col2[16];
	char sv[]="SAVE";
	char ld[]="LOAD";
	char s1[25],s2[25];
	int c1, c2;
	if(turn == 1 && game == 'P'){
		cout << "Enter Column for Player 1 or SAVE/LOAD filename : " << endl ;
		cin.getline(s1,25);
		devine(s1,col1,col2);
		if(isSimilar(col1,sv))
			save(board,size,game,turn,col2);
		else if(isSimilar(col1,ld))
			load(board,size,game,turn,col2);
		else{
			toUpperCase(s1[0]);
			c1 = convertCharToInt(s1[0]);
			ifLegal(board,size,c1,s1[0]);
			changeBoard(board,letter1,c1,size);
			printBoard(board,size);	
			turn=2;
		}
	}
	if(totalCheck(board,size) != 1 && turn == 2 && game == 'P'){
		cout << "Enter Column for Player 2 or SAVE/LOAD filename : " << endl;
		cin.getline(s2,25);
		devine(s2,col1,col2);
		if(isSimilar(col1,sv))
			save(board,size,game,turn,col2);
		else if(isSimilar(col1,ld))
			load(board,size,game,turn,col2);
		else{
			toUpperCase(s2[0]);
			c2 = convertCharToInt(s2[0]);			
			ifLegal(board,size,c2,s2[0]);		
			changeBoard(board,letter2,c2,size);
			printBoard(board,size);	
			turn = 1;
		}		
	}	
	while(game=='C'){												//
		if(boardIsEmpty(board,size)&&totalCheck(board,size) != 1)   //
			takeMoveVsPC(board,letter1,letter2,size,game,turn);	    //  Bu blok Sadece Player ile oynarken
		else{							        					//  LOAD dan Bilgisayara karsı oynanan
    		cout << "Nobody Win This Game."<< endl;  				//	oyuna geçer ise calısacak... 
    		break;													//	
		}															//
	}						 	 									//
}

void versusComputer(char board[20][20], int size, char game){
	char letter_user = 'O', letter_PC = 'X';
	int num, turn=1;
	
	makeBoard(board,size);
	printBoard(board,size);   
	
    do{
    	if(boardIsEmpty(board,size))
    		takeMoveVsPC(board,letter_PC,letter_user,size,game,turn);
    	else{
    		cout << "Nobody Win This Game."<<endl;
    		break;
		}
	}while(totalCheck(board,size) != 1);
	
	winningMessage(board,size);
}

void takeMoveVsPC(char board[20][20], const char letter1,const char letter2, int size,char game, int & turn){
	char col1[16],col2[16];
	char sv[]="SAVE";
	char ld[]="LOAD";
	int c1,i,j,num;
	char s1[25];
	
	if(turn==1 && game=='C'){
		cout << "Enter Column for Player or SAVE/LOAD filename : "<<endl ;
		cin.getline(s1,25);
		devine(s1,col1,col2);
		if(isSimilar(col1,sv))
			save(board,size,game,turn,col2);
		else if(isSimilar(col1,ld))
			load(board,size,game,turn,col2);
		else{
			toUpperCase(s1[0]);
			c1 = convertCharToInt(s1[0]);
			ifLegal(board,size,c1,s1[0]);
			changeBoard(board,letter2,c1,size);
			printBoard(board,size);	
			turn = 2;
		}
	}
	if(totalCheck(board,size) != 1 && turn == 2 && game == 'C'){
		putPC(board,size);
		turn = 1 ;	
	}
	while(game=='P'){
		if(boardIsEmpty(board,size)&&totalCheck(board,size) != 1)   //
			takeMoveVsUsers(board,letter1,letter2,size,game,turn);  //  Bu blok Sadece Bilgisayar ile oynarken
		else{													    //  LOAD dan Playera karsi oynanan
    		cout << "Nobody Win This Game."<<endl;  				//	oyuna geçer ise calısacak... 
    		break;													//
		}															//
	}
}

void putPC(char board[20][20], int size){
	int i, j, num;
	if(totalCheck(board,size) != 1){
		for(i=size-1 ;i>=0; --i){
			for(j=0 ;j<size; ++j){
				if(board[i][j]=='O'&&board[i-1][j]=='.'){
					board[i-1][j] = 'X';
					printBoard(board,size);
					return;
				}
				else if(board[i][j]=='O'&&board[i][j-1]=='.'){
					board[i][j-1] = 'X';
					printBoard(board,size);
					return;
				}					
				else if(board[i][j]=='O'&&board[i][j+1]=='.'){
					board[i][j+1] = 'X';
					printBoard(board,size);
					return;
				}					
				else if(board[i][j]=='O'&&board[i-1][j-1]=='.'){
					board[i-1][j-1] = 'X';
					printBoard(board,size);
					return;
				}
				else if(board[i][j]=='O'&&board[i-1][j+1]=='.'){
					board[i-1][j+1] = 'X';
					printBoard(board,size);
					return;
				}	
				else{
					num = rand() % size; //size'a kadar bir sayý verecek.
					changeBoard(board,'X',num,size);
					printBoard(board,size);
					return;
				}	
			}
		}
	}
}

bool isSimilar(char str1[16],char str2[16]){
	auto result=1;
	decltype(result) i ;
	for(i=0;str1[i]!='\0';++i){
		if(str1[i]!=str2[i])
			result = 0;
	}
	return result;
}

void devine(char str[25], char first[10], char second[20]){
	int i,k;
	
	for(i=0 ;str[i]!='\0'; ++i){
		if(str[i]!=' ')
			first[i] = str[i];
		else{
			first[i] = '\0';
			k = i+1;
			break;	
		}
	}
	i=0;
	while(str[k]!='\0' && str[k]!=' '){
		second[i] = str[k];
		++i;
		++k;
	}
	second[i] = '\0';
}

void ifLegal(char board[20][20], int size, int & column, char & col_name){
	
	while(!columnIsEmpty(board,size,column)){
		cerr << "FAULT! Enter another one : "<<endl;
		cin >> col_name;
		toUpperCase(col_name);
		column = convertCharToInt(col_name);
		cin.ignore();
	}
	
	while(!( ((col_name>='A' && col_name<='Z') || (col_name>='a' && col_name<='z')) && column<size )){
		cerr << "FAULT! Enter another one : "<<endl;
		cin >> col_name;
		toUpperCase(col_name);
		column = convertCharToInt(col_name);
		cin.ignore();
		while(!columnIsEmpty(board,size,column)){
			cerr << "FAULT! Enter another one : "<<endl;
			cin >> col_name;
			toUpperCase(col_name);
			column = convertCharToInt(col_name);
			cin.ignore();
		}
	}
}

void changeBoard(char board[20][20], const char letter, int column, int size){
	int i;
	for(i=size-1 ;i>=0; --i){
		if(board[i][column] == '.'){
			board[i][column] = letter ;
			break;
		}
	}
}

bool columnIsEmpty(char board[20][20],int size, int column){
	int i;
	for(i=size-1 ;i>=0; --i){
		if(board[i][column] == '.')
			return 1;
	}
	return 0;
}

bool boardIsEmpty(char board[20][20], int size){
	int i;
	for(i=0 ;i<size; ++i){
		if(columnIsEmpty(board,size,i))
			return 1;
	}
	return 0;
}

int convertCharToInt(const char c){
	int i;
	if(c>='A' && c<='Z')
		i = c-65;  // 65 from ASCII Table
	return i;
}

void makeBoard(char board[20][20] , int size){
	int i,j;
	for(i=0 ;i<size; ++i){
		for(j=0 ;j<size; ++j)
			board[i][j] = '.' ;
	}
}

void printBoard(char board[20][20], int size){
	int i,j;
	char k = 'a';
	for(i=0 ;i<size; ++i, ++k)
		cout << k ;
	cout << endl;	
	for(i=0 ;i<size; ++i){
		for(j=0 ;j<size; ++j)
			cout << board[i][j] ;
		cout << endl;
	}
}

void winningMessage(char board[20][20], int size){
	int i, j;
	char c;
	printBoard(board,size);
	for(i=0 ;i<size; ++i){
		for(j=0 ;j<size; ++j){
			if(board[i][j]>='a' && board[i][j]<='z'){
				c = board[i][j];
				break;
			}
		}
	}
	if(c=='x')
		cout << "Player 1 Win This Game ... " <<endl;
	else if(c=='o')
		cout << "Player 2 Win This Game ... " <<endl;
}

int horizonalCheck(char board[20][20], int size){
	int row,col,i=0, k;
	char letter;
	for(row=size-1 ;row>=0; --row){
		for(col=0 ;col<size; ++col){	
			if(board[row][col] != '.'){
				letter = board[row][col] ;
				if(board[row][col+1] == letter && board[row][col+2] == letter && board[row][col+3] == letter){
					i = 1;
					for(k=0;k<4;++k)
						toLowerCase(board[row][col+k]);
				}
			}
		}
	}
	return i;
}

int verticalCheck(char board[20][20], int size){
	int row,col,i=0,k;
	char letter;
	for(col=0 ;col<size; ++col){
		for(row=size-1 ;row>=0; --row){	
			if(board[row][col] != '.'){
				letter = board[row][col] ;
				if(board[row-1][col] == letter && board[row-2][col] == letter && board[row-3][col] == letter){
					i = 1;
					for(k=0;k<4;++k)
						toLowerCase(board[row-k][col]);
				}
			}
		}
	}
	return i;
}

int diagonalCheck(char board[20][20], int size){
	int row,col,i=0,k;
	char letter;
	for(row=size-1 ;row>=0; --row){
		for(col=0 ;col<size; ++col){
			if(board[row][col] != '.'){
				letter = board[row][col] ;
				if(board[row-1][col+1] == letter && board[row-2][col+2] == letter && board[row-3][col+3] == letter){
					i = 1;
					for(k=0;k<4;++k)
						toLowerCase(board[row-k][col+k]);
				}
				else if(board[row-1][col-1] == letter && board[row-2][col-2] == letter && board[row-3][col-3] == letter){
					i = 1;	
					for(k=0;k<4;++k)
						toLowerCase(board[row-k][col-k]);
				}
			}
		}
	}
	return i;	
}	

int totalCheck(char board[20][20], int size){
	return(horizonalCheck(board, size) || verticalCheck(board, size) || diagonalCheck(board,size));
}

void toUpperCase(char & c){
	if(c>='a' && c<='z')
		c = c +'A'-'a';
}
void toLowerCase(char & c){
	if(c>='A' && c<='Z')
		c = c +'a'-'A';
}
