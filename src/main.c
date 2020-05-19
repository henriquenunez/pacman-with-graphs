#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define WIDTH 30
#define HEIGHT 15 

// Curses colors
#define GAME_COLOR_BLACK 1
#define GAME_COLOR_BLUE 2
#define GAME_COLOR_YELLOW 3
#define GAME_COLOR_RED 4

// Curses pairs
#define PAIR_BACKGROUND 1
#define PAIR_WALL 2
#define PAIR_PACMAN 3
#define PAIR_GHOST 4

char game_template[HEIGHT][WIDTH] ={{"******************************"},
									{"*             **             *"},
									{"* **** *** ******** *** **** *"},
									{"* *                        * *"},
									{"* * **********  ********** * *"},
									{"*                            *"},
									{"***** ***** **  ** ***** *****"},
									{"      *   * *    * *   *      "},
									{"***** ***** ****** ***** *****"},
									{"*                            *"},
									{"* * **********  ********** * *"},
									{"* *                        * *"},
									{"* **** *** ******** *** **** *"},
									{"*             **             *"},
									{"******************************"}};

void setup_curses();
void draw_game(WINDOW *win, GRAPH *graph, PAIR pacman, PAIR ghost);
void move_pacman(GRAPH *graph, PAIR *pacman);
void move_ghost(GRAPH *graph, PAIR *ghost);

int main(int argc, char *argv[]) {
	//--- Initilize game variables ---//
	char game_running = 1;
	PAIR ghost = {WIDTH/2, HEIGHT/2};
	PAIR pacman = {1, 1};
	GRAPH* graph = create_graph(10,10);

	setup_curses();

	//--- Create game window ---//
	int maxX=0, maxY=0;
	// Get window size
	getmaxyx(stdscr, maxY, maxX);
	// Create window (posY, posX, offsetY, offsetX)
	WINDOW *game  = newwin(HEIGHT, WIDTH, maxY/2-HEIGHT/2, maxX/2-WIDTH/2);
	refresh();

	// Run game until pacman eat the ghost
	while(game_running)
	{
		draw_game(game, graph, pacman, ghost);
		usleep(1*1000000);

		move_ghost(graph, &ghost);
		move_pacman(graph, &pacman);

		if(pacman.first == ghost.first && pacman.second == ghost.second)
			game_running = 0;
	}

	// Destroy the window
	endwin();
	delete_graph(graph);

	return 0;
}

void setup_curses()
{
	//--- Initialize window ---//
	initscr();
	noecho();
	curs_set(FALSE);

	if (has_colors() == FALSE) {
		endwin();
			printf("Your terminal does not support colors\n");
		exit(1);
	} 
	start_color();

	// Create colors
	init_color(GAME_COLOR_BLACK, 200, 200, 200);
	init_color(GAME_COLOR_RED, 1000, 0, 0);
	init_color(GAME_COLOR_BLUE, 0, 0, 1000);
	init_color(GAME_COLOR_YELLOW, 1000, 1000, 0);

	// Create pairs
	init_pair(PAIR_BACKGROUND, GAME_COLOR_BLACK, GAME_COLOR_BLACK);	
	init_pair(PAIR_WALL, GAME_COLOR_BLUE, GAME_COLOR_BLUE);	
	init_pair(PAIR_PACMAN, GAME_COLOR_YELLOW, GAME_COLOR_BLACK);	
	init_pair(PAIR_GHOST, GAME_COLOR_RED, GAME_COLOR_BLACK);	

	// Set background color
	bkgd(COLOR_PAIR(PAIR_BACKGROUND));
}

void draw_game(WINDOW *win, GRAPH *graph, PAIR pacman, PAIR ghost)
{
	int x,y;
	// Clear window
	wclear(win);

	// Draw game template
	wattr_on(win, COLOR_PAIR(PAIR_WALL), NULL);
	for(x=0;x<WIDTH;x++)
	{
		for(y=0;y<HEIGHT;y++)
		{
			if(game_template[y][x]=='*')
				mvwprintw(win, y, x, "*");

			//mvwprintw(win, y, 0, "*");
			//mvwprintw(win, y, WIDTH-1, "*");
			//mvwprintw(win, 0, x, "*");
			//mvwprintw(win, HEIGHT-1, x, "*"); 
		}
	}
	wattr_off(win, COLOR_PAIR(PAIR_WALL), NULL);

	// Draw graph 
	wattr_on(win, COLOR_PAIR(PAIR_BACKGROUND), NULL);
	for(x=0;x<WIDTH;x+=2)
	{
		for(y=0;y<HEIGHT;y++)
		{
			//mvwprintw(win, y, x, " ");
		}
	}
	wattr_off(win, COLOR_PAIR(PAIR_BACKGROUND), NULL);

	wattr_on(win, COLOR_PAIR(PAIR_GHOST), NULL);
	mvwprintw(win, ghost.second, ghost.first, "g");
	wattr_off(win, COLOR_PAIR(PAIR_GHOST), NULL);

	wattr_on(win, COLOR_PAIR(PAIR_PACMAN), NULL);
	mvwprintw(win, pacman.second, pacman.first, "o");
	wattr_off(win, COLOR_PAIR(PAIR_PACMAN), NULL);
	
	// Refresh window 
	wrefresh(win);
}

void move_pacman(GRAPH *graph, PAIR *pacman)
{

}

void move_ghost(GRAPH *graph, PAIR *ghost)
{

}
