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
GRAPH* create_game_graph();
void draw_game(WINDOW *win, GRAPH *graph, PAIR pacman, PAIR ghost);
void move_pacman(GRAPH *graph, PAIR *pacman, PAIR ghost);
void move_ghost(GRAPH *graph, PAIR *ghost, PAIR pacman);

int main(int argc, char *argv[]) {
	//--- Initilize game variables ---//
	char game_running = 1;
	PAIR ghost = {WIDTH/2, HEIGHT/2};
	PAIR pacman = {1, 1};
	GRAPH* graph = create_game_graph();

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

		move_ghost(graph, &ghost, pacman);
		move_pacman(graph, &pacman, ghost);

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

GRAPH* create_game_graph()
{
	GRAPH *graph = create_graph(WIDTH,HEIGHT);
	for(int x=0;x<WIDTH;x++)
	{
		for(int y=0;y<HEIGHT;y++)
		{
			PAIR curr = {x,y};
			if(game_template[y][x]=='*')
				continue;

			// Check top
			if(y-1>0)
			{
				PAIR top = {x,y-1};
				if(game_template[y-1][x]==' ')
					insert_edge_graph(graph, curr, top);
			}
			else
			{
				// Connect top with bottom
				PAIR top = {x,HEIGHT-1};
				if(game_template[HEIGHT-1][x]==' ')
					insert_edge_graph(graph, curr, top);
			}

			// Check left
			if(x-1>0)
			{
				PAIR left = {x-1,y};
				if(game_template[y][x-1]==' ')
					insert_edge_graph(graph, curr, left);
			}
			else
			{
				// Connect right with left
				PAIR left = {WIDTH-1,y};
				if(game_template[y][WIDTH-1]==' ')
					insert_edge_graph(graph, curr, left);
			}
			
			// Check bottom
			if(y+1<HEIGHT)
			{
				PAIR bottom = {x,y+1};
				if(game_template[y+1][x]==' ')
					insert_edge_graph(graph, curr, bottom);
			}
			else
			{
				// Connect top with bottom
				PAIR bottom = {x,0};
				if(game_template[0][x]==' ')
					insert_edge_graph(graph, curr, bottom);
			}
			
			// Check right
			if(x+1<WIDTH)
			{
				PAIR right = {x+1,y};
				if(game_template[y][x+1]==' ')
					insert_edge_graph(graph, curr, right);
			}
			else
			{
				// Connect right with left
				PAIR right = {0,y};
				if(game_template[y][0]==' ')
					insert_edge_graph(graph, curr, right);
			}
		}
	}
	return graph;
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

void move_pacman(GRAPH *graph, PAIR *pacman, PAIR ghost)
{
	BFS_fill_distance_graph(graph, *pacman, ghost);
	// Values getting bigger from ghost to pacman -> choose lower number
	PAIR best_position = {-1,-1};
	int best_bfs_value = WIDTH*HEIGHT;// Works like infinity
	PAIR curr_checking;
	int curr_bfs_value;

	PAIR positions_to_check[4] = {{pacman->first, (pacman->second-1)%HEIGHT},// Top
								{(pacman->first+1)%WIDTH, pacman->second},// Right
								{pacman->first, (pacman->second+1)%HEIGHT},// Bottom
								{(pacman->first-1)%WIDTH, pacman->second}};// Left

	for(int i=0;i<4;i++)
	{
		curr_checking = positions_to_check[i];
		curr_bfs_value = value_at_vertex_graph(graph, curr_checking);
		if(curr_bfs_value!=0 && curr_bfs_value<best_bfs_value)
		{
			// Position is not an obstacle and is better than the best position
			best_bfs_value = curr_bfs_value;
			best_position = curr_checking;
		}
	}

	// If some position to walk was found...
	if(best_position.first!=-1)
		*pacman = best_position;
}

void move_ghost(GRAPH *graph, PAIR *ghost, PAIR pacman)
{
	BFS_fill_distance_graph(graph, *ghost, pacman);
	// Values getting bigger from pacman to ghost -> choose higher number
	PAIR best_position = {-1,-1};
	int best_bfs_value = 0;
	PAIR curr_checking;
	int curr_bfs_value;

	PAIR positions_to_check[4] = {{ghost->first, (ghost->second-1)%HEIGHT},// Top
								{(ghost->first+1)%WIDTH, ghost->second},// Right
								{ghost->first, (ghost->second+1)%HEIGHT},// Bottom
								{(ghost->first-1)%WIDTH, ghost->second}};// Left

	for(int i=0;i<4;i++)
	{
		curr_checking = positions_to_check[i];
		curr_bfs_value = value_at_vertex_graph(graph, curr_checking);
		if(curr_bfs_value!=0 && curr_bfs_value>best_bfs_value)
		{
			// Position is not an obstacle and is better than the best position
			best_bfs_value = curr_bfs_value;
			best_position = curr_checking;
		}
	}

	// If some position to walk was found...
	if(best_position.first!=0)
		*ghost = best_position;
}
