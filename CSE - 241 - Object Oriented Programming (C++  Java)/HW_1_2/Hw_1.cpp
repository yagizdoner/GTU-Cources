#include <iostream>
#include <cstdlib> // Random Sayý Alabilmek Ýçin
using namespace std;

void makeBoard(char board[20][20], int size);//Board'u istenilen size'a göre oluþturacak.
void printBoard(char board[20][20], int size);// Board'u ekrana basacak.
void changeBoard(char board[20][20], char letter, int column, int size);//Input a göre board'u deðiþtirecek.
void takeMoveVsUsers(char board[20][20], char letter1,char letter2, int size);// 2 Kullanýcýdan da hareketlerin alýnýp iþleneceði yer.
void takeMoveVsPC(char board[20][20], char letter1,char letter2, int size);// Kullanýcý ve PC hareketlerinin alýnýp iþleneceði yer.
int horizonalCheck(char board[20][20], int size); // yatay kontrolü yapacak.
int verticalCheck(char board[20][20], int size); // dikey kontrolü yapacak.
int diagonalCheck(char board[20][20], int size); // çapraz kontrolü yapacak.
int totalCheck(char board[20][20], int size); // yatay, dikey ve çapraz olarak 4'lülüðü kontrol edecek ve 4'lü varsa 1 yoksa 0 return edecek.
void versusUsers(char board[20][20], int size); // Ýki kullanýcý arasýndaki oyunu baþlatacak.
void versusComputer(char board[20][20], int size); // Bilgisayar ve Kullanýcý arasýndaki Oyunu Baþlatacak.
void putPC(char board[20][20], int size); //  Bilgisayarýn Otomatik Hareketlerini Gerçekleþtirecek.
int convertCharToInt(char c); // girilen harfin array de tam sayý alarak kullanýlabilmesi için ...
bool columnIsEmpty(char board[20][20],int size, int column);  // if return 1 : column is empty, return 0 : column is full.
void ifLegal(char board[20][20], int size, int & column, char & col_name); // Girilen girdinin board'a uygunluðuna bakýlýp duruma göre yeniden girdi istenilecek.
bool boardIsEmpty(char board[20][20], int size); // if return 1 : board is empty, return 0 : board is full.
void toUpperCase(char & c); // lower case to Upper case.
void toLowerCase(char & c); // upper case to Lower case.
void winningMessage(char board[20][20], int size); // Galibiyet Durumununa göre sonucu ekrana basacak.

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
	char board[20][20];
	
	if(game == 'P')
		versusUsers(board, size);
	else // Game C 'den baþka bir þey olamayacaðý için boþa kontrol yapmayacak.
		versusComputer(board, size);
	
	return 0;
}

void versusUsers(char board[20][20], int size){
	char letter1 = 'X', letter2 = 'O';
	
	makeBoard(board,size);
	printBoard(board,size);   
	 
    do{
    	if(boardIsEmpty(board,size))
    		takeMoveVsUsers(board,letter1,letter2,size);
    	else{
    		cout << "Nobody Win This Game.";
    		break;
		}
	}while(totalCheck(board,size) != 1);
	
	winningMessage(board,size);
}

void versusComputer(char board[20][20], int size){
	char letter_user = 'O', letter_PC = 'X';
	int num;
	
	makeBoard(board,size);
	printBoard(board,size);   
	
    do{
    	if(boardIsEmpty(board,size))
    		takeMoveVsPC(board,letter_PC,letter_user,size);
    	else{
    		cout << "Nobody Win This Game.";
    		break;
		}
	}while(totalCheck(board,size) != 1);
	
	winningMessage(board,size);
}

void takeMoveVsPC(char board[20][20], char letter1,char letter2, int size){
	char col1;
	int c1,i,j,num;
	
	cout << "Enter Column for Player : " ;
	cin >> col1;
	toUpperCase(col1);
	c1 = convertCharToInt(col1);
	ifLegal(board,size,c1,col1);
	changeBoard(board,letter2,c1,size);
	printBoard(board,size);	
	
	putPC(board,size);
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

void takeMoveVsUsers(char board[20][20], char letter1,char letter2, int size){
	char col1,col2;
	int c1, c2;
	
	cout << "Enter Column for Player 1 : " ;
	cin >> col1;
	toUpperCase(col1);
	c1 = convertCharToInt(col1);
	ifLegal(board,size,c1,col1);
	changeBoard(board,letter1,c1,size);
	printBoard(board,size);	
	
	if(totalCheck(board,size) != 1){
		cout << "Enter Column for Player 2 : " ;
		cin >> col2;
		toUpperCase(col2);
		c2 = convertCharToInt(col2);
		
		ifLegal(board,size,c2,col2);
		
		changeBoard(board,letter2,c2,size);
		printBoard(board,size);	
	}	
}

void ifLegal(char board[20][20], int size, int & column, char & col_name){
	
	while(!columnIsEmpty(board,size,column)){
		cerr << "FAULT! Enter another one : ";
		cin >> col_name;
		toUpperCase(col_name);
		column = convertCharToInt(col_name);
	}
	
	while(!( ((col_name>='A' && col_name<='Z') || (col_name>='a' && col_name<='z')) && column<size )){
		cerr << "Enter a Valid Character : ";
		cin >> col_name;
		toUpperCase(col_name);
		column = convertCharToInt(col_name);
		while(!columnIsEmpty(board,size,column)){
			cerr << "FAULT! Enter another one : ";
			cin >> col_name;
			toUpperCase(col_name);
			column = convertCharToInt(col_name);
		}
	}
}

void changeBoard(char board[20][20], char letter, int column, int size){
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

int convertCharToInt(char c){
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
		cout << "Player 1 Win This Game ... " ;
	else if(c=='o')
		cout << "Player 2 Win This Game ... " ;
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
