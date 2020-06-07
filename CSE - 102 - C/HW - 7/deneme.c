#include <stdio.h>
typedef enum _tileType {BORDER, WALL, EMPTY, USED, START} TILE_TYPE;
//typedef enum _pathType {DISTANCE, COMFORT, DANGER} PATH_TYPE;
//typedef enum _printType {P_DISTANCE, P_COMFORT, P_DANGER, P_TRAP} PRINT_TYPE;

typedef struct _tiles{
	TILE_TYPE type;
	int distance;
	int dangerLevel;
	int comfortLevel;
	int trapDamage;
}TILES;


typedef struct _coord{
	int x;
	int y;
}Coord;



void main(){
	int a;
	Coord co;
	co.x = 1;
	co.y = 1;
//	TILES maze[5][5];
	TILES maze[5][5] = {
				{WALL,BORDER,BORDER,WALL,WALL},
				{WALL,EMPTY,EMPTY,EMPTY,WALL},
				{WALL,EMPTY,EMPTY,EMPTY,WALL},
				{WALL,EMPTY,EMPTY,EMPTY,WALL},
				{WALL,WALL,WALL,WALL,WALL}
				 }; 
	a = isExit(maze,co);
	printf("%d",a);
}

int isExit(TILES maze[5][5], Coord currentTile){
	int result = 0;
	if(maze[currentTile.x][currentTile.y].type == EMPTY){
		if(maze[currentTile.x-1][currentTile.y].type == BORDER)
			result = 1;
		else if(maze[currentTile.x+1][currentTile.y].type == BORDER)
			result = 1;
		else if(maze[currentTile.x][currentTile.y-1].type == BORDER)
			result = 1;
		else if(maze[currentTile.x][currentTile.y+1].type == BORDER)
			result = 1;
	}
	return result;
}
