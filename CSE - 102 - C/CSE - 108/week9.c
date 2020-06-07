int isStuck(TILES maze[100][100], int currentTile[]){
	int x = currentTile[0];
	int y = currentTile[1];
	
	int leftX = x-1;
	int rightX = x+1;
	
	int upY = y-1;
	int downY = y+1;

	if( maze[leftX][y] != EMPTY && maze[rightX][y] != EMPTY &&
		maze[x][upY]   != EMPTY && maze[x][downY]  != EMPTY ){

		return 1;
	}else{
		return 0;
	}
}



int isExit(TILES maze[100][100], int currentTile[]){
	int x = currentTile[0];
	int y = currentTile[1];
	
	int leftX = x-1;
	int rightX = x+1;
	
	int upY = y-1;
	int downY = y+1;

	if( maze[leftX][y] == BORDER || maze[rightX][y] == BORDER ||
		maze[x][upY]   == BORDER || maze[x][downY]  == BORDER ){

		return 1;
	}else{
		return 0;
	}
}



int exitFromMaze(TILES maze[100][100], int currentTile[2]){
	int x = currentTile[0];
	int y = currentTile[1];
	
	int leftX = x-1;
	int rightX = x+1;
	
	int upY = y-1;
	int downY = y+1;

	int totalExits = 0;
	int nextTile[2];
	
	if (maze[x][y] != EMPTY){
		return -1;
	}
	
	maze[x][y] = USED;


	if( isStuck(maze, currentTile) ){
		if( isExit(maze, currentTile) ){
			return totalExits + 1;
		}else{
			return 0;
		}
	}else{
		if(maze[leftX][y] == EMPTY){
			nextTile[0] = leftX;
			nextTile[1] = y;
			totalExits += exitFromMaze(maze, nextTile);
			
		}
		if(maze[rightX][y] == EMPTY){
			nextTile[0] = rightX;
			nextTile[1] = y;
			totalExits += exitFromMaze(maze, nextTile);
		}
		if(maze[x][upY] == EMPTY){
			nextTile[0] = x;
			nextTile[1] = upY;
			totalExits += exitFromMaze(maze, nextTile);
		}
		if(maze[x][downY] == EMPTY){
			nextTile[0] = x;
			nextTile[1] = downY;
			totalExits += exitFromMaze(maze, nextTile);
		}
		if( isExit(maze, currentTile) ){
			return totalExits + 1;
		}else{
			return totalExits;
		}
	}
}
