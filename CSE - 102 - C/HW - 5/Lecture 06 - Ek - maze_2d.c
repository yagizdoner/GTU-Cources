#include <stdio.h>
#include <stdlib.h>

#define MAZE_NUM_ROWS 8
#define MAZE_NUM_COLS 8

void show_current_game(int maze[][MAZE_NUM_ROWS]);
int get_move_and_apply(int maze[][MAZE_NUM_COLS]);


void main(void) {

	/* Game configuration - 1: wall, 0: empty space, 2: player, 3: target */
	int maze[MAZE_NUM_ROWS][MAZE_NUM_COLS] = {
		{1,1,1,1,1,1,3,1},
		{1,0,0,0,1,0,0,1},
		{1,0,1,2,1,0,1,1},
		{1,0,1,0,1,0,0,1},
		{1,0,1,0,0,1,0,1},
		{1,0,1,1,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	int game_continue = 1;  /* Flag 1: continue playing, 0: quit game */

	do {
		show_current_game(maze);
		game_continue = get_move_and_apply(maze);
	} while (game_continue);
}


void show_current_game(int maze[][MAZE_NUM_COLS]) {
	int r, c;
	for (r=0; r<MAZE_NUM_ROWS; r++) {
		for (c=0; c<MAZE_NUM_COLS; c++) {
			printf("%d ", maze[r][c]);
		}
		printf("\n");
	}
}


void find_current_location(int maze[][MAZE_NUM_COLS], int * cr, int * cc) {
	int r, c, found;
	for (r=0, found=0; r<MAZE_NUM_ROWS && !found; r++) {
		for (c=0; c<MAZE_NUM_COLS && !found; c++) {
			if (maze[r][c]==2) {
				*cr = r;
				*cc = c;
				found = 1;
			}
		}
	}
	if (!found) {
		printf("Something is wrong with your maze, I cannot find the player...\n");
		exit(0);
	}
	return;
}


void move_down(int maze[][MAZE_NUM_COLS]) {
	int cr, cc;
	find_current_location(maze, &cr, &cc);
	if (cr<MAZE_NUM_ROWS-1 && maze[cr+1][cc]==3) {
		/* game over */
	}
	else if (cr<MAZE_NUM_ROWS-1 && maze[cr+1][cc]==0) {
		maze[cr][cc] = 0;
		maze[cr+1][cc] = 2;
	}
}

void move_up(int maze[][MAZE_NUM_COLS]) {
	int cr, cc;
	find_current_location(maze, &cr, &cc);
	if (cr>0 && maze[cr-1][cc]==3) {
		/* game over */
	}
	else if (cr>0 && maze[cr-1][cc]==0) {
		maze[cr][cc] = 0;
		maze[cr-1][cc] = 2;
	}
}

void move_left(int maze[][MAZE_NUM_COLS]) {
	int cr, cc;
	find_current_location(maze, &cr, &cc);
	if (cc>0 && maze[cr][cc-1]==3) {
		/* game over */
	}
	else if (cc>0 && maze[cr][cc-1]==0) {
		maze[cr][cc] = 0;
		maze[cr][cc-1] = 2;
	}
}

void move_right(int maze[][MAZE_NUM_COLS]) {
	int cr, cc;
	find_current_location(maze, &cr, &cc);
	if (cc<MAZE_NUM_COLS-1 && maze[cr][cc+1]==3) {
		/* game over */
	}
	else if (cc<MAZE_NUM_COLS-1 && maze[cr][cc+1]==0) {
		maze[cr][cc] = 0;
		maze[cr][cc+1] = 2;
	}
}

int get_move_and_apply(int maze[][MAZE_NUM_COLS]) {
	char move, junk;
	int result = 1;
	printf("Your move [l,r,u,d,e]: ");
	scanf("%c%c", &move, &junk);
	switch (move) {
	case 'u': move_up(maze); break;
	case 'd': move_down(maze); break;
	case 'l': move_left(maze); break;
	case 'r': move_right(maze); break;
	case 'e': result = 0;
	default: break;
	}
	return result; 
}