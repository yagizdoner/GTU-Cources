#include <stdio.h>
#define GRIDSIZE 4

/*  YAÐIZ DÖNER  -  141044062  */

typedef enum {mined, empty, flaggedMined, flaggedEmpty, closedEmpty, closedMined}cell;

void printGrid (cell grid[][GRIDSIZE]);
int openCell(cell grid[][GRIDSIZE], int x, int y); 		// return value int result = -2 when the cell is not opened with the case of illegal location; or flagged cell.
int flagCell(cell grid[][GRIDSIZE], int x, int y); 		// return value int result = -2 when the cell is not flagged with the case of illegal location; or already flagged cell.
int isCellEmpty(cell grid[][GRIDSIZE], int x, int y);   //return value int result=0 if the cell is not an empty cell and result=1 the cell is an empty cell.
int isLocationLegal(int x, int y); 						//return value int result=0 if the location is illegal and result=1 if the location is legal(in the grid).
void initGrid(cell grid[][GRIDSIZE]);
int asMain(); 

int main(void){
	asMain();
	return(0);
}

int asMain(){
	int closed_empty_num=0;
	int empty_num=0;
	int i, j;
	char f_or_o;
	int game_continue=1, x, y, count = 0;
	cell grid[GRIDSIZE][GRIDSIZE];
	initGrid(grid);
	printGrid(grid);
	for ( i=0 ; i < GRIDSIZE ; i++) {			//
		for ( j=0 ; j < GRIDSIZE ; j++) {		//	Ýleride do-while döngüsünden
			if(grid[i][j] == closedEmpty)		//  çýkabilmek için 
				closed_empty_num++;				//	baþlangýçtaki
		}										//  boþ yer sayýsýný aldým.
	}											//
	do {
	printf("Your move [flag,open]: ");
	scanf(" %c", &f_or_o);
	printf("Enter Coor. X : ");
	scanf("%d",&x);
   	printf("Enter Coor. Y : ");
	scanf("%d",&y);
	if(grid[x][y] == closedMined && f_or_o == 'o' ){
		printf(" !!!! You Loose the Game. Try Again... !!!!");
		return 0;
	}
	else{
		switch (f_or_o) {
			case 'o': openCell(grid, x, y);
					  count++;
					  break; 
			case 'f': flagCell(grid, x, y);
			 		  count++;
				 	  break;
			default: break;
		}
		printGrid(grid);	
		for ( i=0 ; i < GRIDSIZE ; i++) {								//
			for ( j=0 ; j < GRIDSIZE ; j++) {							// Baþlangýçta aldýðým boþ yer
				if(grid[i][j] == empty || grid[i][j] == flaggedEmpty)	// sayýsý ile karþýlaþtýrabilmek
					empty_num++; 										// için eldeki boþ ve boþ_bayrak
			}															// sayýsýný aldým
		}																//
		if(empty_num == closed_empty_num)
			game_continue = 0 ;
		empty_num = 0;       //  Eðer eþit deðilse döngüde tekrar kullanabilmek adýna sýfýrladým.
	}
	} while (game_continue);
	printf("Congratulations! You win the game with %d moves", count);
	return(0);
}

void initGrid(cell grid[][GRIDSIZE]){
	int i, j;
	cell init_grid[GRIDSIZE][GRIDSIZE] = {
		   {closedEmpty,closedMined,closedMined,closedEmpty},
		   {closedEmpty,closedEmpty,closedMined,closedMined},
		   {closedEmpty,closedEmpty,closedEmpty,closedEmpty},
		   {closedEmpty,closedEmpty,closedEmpty,closedEmpty}
	};
	for ( i=0 ; i < GRIDSIZE ; i++) {
		for ( j=0 ; j < GRIDSIZE ; j++) {
			grid[i][j] = init_grid[i][j];
		}
	}
}

void printGrid(cell grid[][GRIDSIZE]){
	int i, j;
	cell print_grid[GRIDSIZE][GRIDSIZE];    // Orjinal arrayimi deðiþtirmeden yazabilmek 											
	for ( i=0 ; i < GRIDSIZE ; i++) {		//	adýna baþka bir array kullandým.
		for ( j=0 ; j < GRIDSIZE ; j++) {	
			print_grid[i][j] = grid[i][j];
		}
	}
	for ( i=0 ; i < GRIDSIZE ; i++) {
		for ( j=0 ; j < GRIDSIZE ; j++) {
			if(grid[i][j] == closedMined)
				print_grid[i][j] = '.' ;
			else if(grid[i][j] == closedEmpty)
				print_grid[i][j] = '.' ;
			else if(grid[i][j] == empty)
				print_grid[i][j] = 'e' ;
			else if(grid[i][j] == flaggedMined)
				print_grid[i][j] = 'f' ;
			else if(grid[i][j] == flaggedEmpty)
				print_grid[i][j] = 'f' ;
		}
	}
	for ( i=0 ; i < GRIDSIZE ; i++) {
		for ( j=0 ; j < GRIDSIZE ; j++) {
			printf("%c", print_grid[i][j]);
		}
		printf("\n");
	}
	
}

int openCell(cell grid[][GRIDSIZE], int x, int y){

	int result=0;
	
	if( isLocationLegal(x,y) ){
		if( isCellEmpty(grid, x, y) ){
			grid[x][y] = empty ;
			openCell(grid,x-1,y);
			openCell(grid,x,y-1);
			openCell(grid,x+1,y);
			openCell(grid,x,y+1);
		}
		else if( grid[x][y] == closedMined ){
			grid[x][y] == mined ;
		}	
	}	
	else
		result = -2 ;
	return result ;
}	

int flagCell(cell grid[][GRIDSIZE], int x, int y){	
	int result=0;
	if( isLocationLegal(x,y) ) {
		if(grid[x][y] == closedEmpty)
			grid[x][y] = flaggedEmpty;
		else if(grid[x][y] == closedMined)
			grid[x][y] = flaggedMined;				
		else if(grid[x][y] == flaggedEmpty)
			grid[x][y] == closedEmpty;
		else if(grid[x][y] == flaggedMined)
			grid[x][y] == closedMined;
	}
	else
		result = -2 ;
	return result ;
}	

int isCellEmpty(cell grid[][GRIDSIZE], int x, int y){
	int result;
	if( grid[x][y] == closedEmpty )
		result = 1 ;
	else
		result = 0 ;
	return result ;
}

int isLocationLegal(int x, int y){
	int result;
	if( x >= 0 && x < GRIDSIZE && y >= 0 && y < GRIDSIZE)
		result = 1 ;
	else
		result = 0 ;
	return result ;
}

// YAÐIZ DÖNER --- 141044062
