#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define mod(a, b) (((a)%(b) < 0) ? (((a)%(b)) + (b)) : ((a)%(b)))

// Game size
#define WIDTH 30
#define HEIGHT 15 

// Game over size
#define WIDTH_GAME_OVER 50
#define HEIGHT_GAME_OVER 6 

// Help size 
#define WIDTH_HELP 18
#define HEIGHT_HELP 11 

// Curses colors
#define GAME_COLOR_BLACK 1
#define GAME_COLOR_BLUE 2
#define GAME_COLOR_YELLOW 3
#define GAME_COLOR_RED 4
#define GAME_COLOR_GRAY 5

// Curses pairs
#define PAIR_BACKGROUND 1
#define PAIR_WALL 2
#define PAIR_PACMAN 3
#define PAIR_GHOST 4
#define PAIR_GAME_OVER 5
#define PAIR_NUMBERS 6
#define PAIR_HELP 7

char game_template[HEIGHT][WIDTH] ={{"************* ** *************"},
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
									{"************* ** *************"}};

//char game_template[HEIGHT][WIDTH+1] ={{"******************************"},
//								   	  {"*                            *"},
//								      {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"*                            *"},
//								   	  {"******************************"}};


char game_over[HEIGHT_GAME_OVER][WIDTH_GAME_OVER+1] = {{"  __ _  __ _ _ __ ___   ___    _____   _____ _ __ "},
						 {" / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|"},
						 {"| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   "},
						 {" \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   "},
						 {"  __/ |                                           "},
						 {" |___/                                            "}};


char help_template[HEIGHT_HELP][WIDTH_HELP] = {{"----- HELP -----"},
					  {"Move ghost:     "},
					  {"       k        "},
					  {"     h   l      "},
					  {"       j        "},
					  {"                "},
					  {"Quit:           "},
					  {"   <ESQ> or q   "},
					  {"                "},
					  {"Remember:       "},
					  {" Losing is fun! "}};



void setup_curses();
GRAPH* create_game_graph();
void draw_game(WINDOW *win, GRAPH *graph, PAIR pacman, PAIR ghost);
void move_pacman(GRAPH *graph, PAIR *pacman, PAIR ghost);
void move_ghost(GRAPH *graph, PAIR *ghost, PAIR pacman);
void draw_game_over(WINDOW *win);
void draw_help(WINDOW *win);

int main(int argc, char *argv[]) {
	//--- Initilize game variables ---//
	char game_running = 1;
	PAIR ghost = {HEIGHT/2, WIDTH/2};
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
	//--- Create help window ---//
	WINDOW *help_window  = newwin(HEIGHT_HELP, WIDTH_HELP, 0, 0);
	refresh();
	draw_help(help_window);

	//--- Run game until pacman eat the ghost ---//
	BFS_fill_distance_graph(graph, ghost, pacman);
	while(game_running)
	{
		draw_game(game, graph, pacman, ghost);
		usleep(0.1*1000000);

		move_ghost(graph, &ghost, pacman);
		move_pacman(graph, &pacman, ghost);

		if(pacman.first == ghost.first && pacman.second == ghost.second)
			game_running = 0;

	}
	draw_game(game, graph, pacman, ghost);

	//--- Print game over ---//
	WINDOW *game_over_window  = newwin(HEIGHT_GAME_OVER, WIDTH_GAME_OVER, maxY/2-HEIGHT_GAME_OVER/2-HEIGHT/2-3, maxX/2-WIDTH_GAME_OVER/2);
	refresh();

	draw_game_over(game_over_window);

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
	init_color(GAME_COLOR_GRAY, 300, 300, 300);
	init_color(GAME_COLOR_RED, 1000, 0, 0);
	init_color(GAME_COLOR_BLUE, 0, 0, 1000);
	init_color(GAME_COLOR_YELLOW, 1000, 1000, 0);

	// Create pairs
	init_pair(PAIR_BACKGROUND, GAME_COLOR_BLACK, GAME_COLOR_BLACK);	
	init_pair(PAIR_WALL, GAME_COLOR_BLUE, GAME_COLOR_BLUE);	
	init_pair(PAIR_PACMAN, GAME_COLOR_YELLOW, GAME_COLOR_BLACK);	
	init_pair(PAIR_GHOST, GAME_COLOR_RED, GAME_COLOR_BLACK);	
	init_pair(PAIR_GAME_OVER, GAME_COLOR_RED, GAME_COLOR_BLACK);	
	init_pair(PAIR_NUMBERS, GAME_COLOR_GRAY, GAME_COLOR_BLACK);	
	init_pair(PAIR_HELP, GAME_COLOR_YELLOW, GAME_COLOR_BLACK);	

	// Set background color
	bkgd(COLOR_PAIR(PAIR_BACKGROUND));
}

GRAPH* create_game_graph()
{
	GRAPH *graph = create_graph(HEIGHT, WIDTH);
	for(int x=0;x<WIDTH;x++)
	{
		for(int y=0;y<HEIGHT;y++)
		{
			PAIR curr = {y, x};
			if(game_template[y][x]=='*')
				continue;

			PAIR positions_to_link[4] = {{curr.first, mod(curr.second-1,WIDTH)}, // Left
										{mod(curr.first+1,HEIGHT), curr.second}, // Bottom
										{curr.first, mod(curr.second+1,WIDTH)},  // Right
										{mod(curr.first-1,HEIGHT), curr.second}};// Top

			for(int i=0;i<4;i++)
			{
				PAIR pos_to_link = positions_to_link[i];
				if(game_template[pos_to_link.first][pos_to_link.second]==' ')
					insert_edge_graph(graph, curr, pos_to_link);
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
		}
	}
	wattr_off(win, COLOR_PAIR(PAIR_WALL), NULL);

	// Draw graph 
	wattr_on(win, COLOR_PAIR(PAIR_NUMBERS), NULL);
	for(x=0;x<WIDTH;x++)
	{
		for(y=0;y<HEIGHT;y++)
		{
			if(game_template[y][x]!='*')
			{
				PAIR pair = {y,x};
				int value = value_at_vertex_graph(graph, pair);
				if(value<10)
					mvwprintw(win, y, x, "%d",value);
				else
					mvwprintw(win, y, x, "%c",'a'+value-10);
			}
		}
	}
	wattr_off(win, COLOR_PAIR(PAIR_NUMBERS), NULL);

	wattr_on(win, COLOR_PAIR(PAIR_GHOST), NULL);
	mvwprintw(win, ghost.first, ghost.second, "g");
	wattr_off(win, COLOR_PAIR(PAIR_GHOST), NULL);

	wattr_on(win, COLOR_PAIR(PAIR_PACMAN), NULL);
	mvwprintw(win, pacman.first, pacman.second, "o");
	wattr_off(win, COLOR_PAIR(PAIR_PACMAN), NULL);
	
	// Refresh window 
	wrefresh(win);
}

void move_pacman(GRAPH *graph, PAIR *pacman, PAIR ghost)
{
	BFS_reset_distance_graph(graph);
	BFS_fill_distance_graph(graph, ghost, *pacman);
	// Values getting bigger from ghost to pacman -> choose lower number
	PAIR best_position = {-1,-1};
	int best_bfs_value = WIDTH*HEIGHT;// Works like infinity
	PAIR curr_checking;
	int curr_bfs_value;

	PAIR positions_to_check[4] = {{pacman->first, mod(pacman->second-1,WIDTH)},// Left
								{mod(pacman->first+1,HEIGHT), pacman->second},// Bottom
								{pacman->first, mod(pacman->second+1,WIDTH)},// Right
								{mod(pacman->first-1,HEIGHT), pacman->second}};// Top
	// Check best move
	for(int i=0;i<4;i++)
	{
		curr_checking = positions_to_check[i];

		// Check if can eat ghost
		if(curr_checking.first==ghost.first && curr_checking.second==ghost.second)
		{
			best_position = curr_checking;
			break;
		}

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
	//------------- Control ghost with BFS ------------//
	//BFS_reset_distance_graph(graph);
	//BFS_fill_distance_graph(graph, pacman, *ghost);
	//// Values getting bigger from pacman to ghost -> choose higher number
	//PAIR best_position = {-1,-1};
	//int best_bfs_value = 0;
	//PAIR curr_checking;
	//int curr_bfs_value;

	//PAIR positions_to_check[4] = {{ghost->first, mod(ghost->second-1,WIDTH)},// Left
	//							{mod(ghost->first+1,HEIGHT), ghost->second},// Top
	//							{ghost->first, mod(ghost->second+1,WIDTH)},// Right
	//							{mod(ghost->first-1,HEIGHT), ghost->second}};// Bottom

	//for(int i=0;i<4;i++)
	//{
	//	curr_checking = positions_to_check[i];
	//	curr_bfs_value = value_at_vertex_graph(graph, curr_checking);
	//	if(curr_bfs_value!=0 && curr_bfs_value>best_bfs_value)
	//	{
	//		// Position is not an obstacle and is better than the best position
	//		best_bfs_value = curr_bfs_value;
	//		best_position = curr_checking;
	//	}
	//}

	//// If some position to walk was found...
	//if(best_position.first!=0)
	//	*ghost = best_position;
	

	//------------- Control ghost with keyboard ------------//
	int key = getch();
	switch(key)
	{
		case 'k':
			if(game_template[mod(ghost->first-1,HEIGHT)][ghost->second]!='*')
			{
				ghost->first = mod(ghost->first-1,HEIGHT);
				ghost->second = ghost->second;
			}
			break;
		case 'h':
			if(game_template[ghost->first][mod(ghost->second-1,WIDTH)]!='*')
			{
				ghost->first = ghost->first;
				ghost->second = mod(ghost->second-1,WIDTH);
			}
			break;
		case 'j':
			if(game_template[mod(ghost->first+1,HEIGHT)][ghost->second]!='*')
			{
				ghost->first = mod(ghost->first+1,HEIGHT);
				ghost->second = ghost->second;
			}
			break;
		case 'l':
			if(game_template[ghost->first][mod(ghost->second+1,WIDTH)]!='*')
			{
				ghost->first = ghost->first;
				ghost->second = mod(ghost->second+1,WIDTH);
			}
			break;
		case 27:// <ESQ>
		case 'q':
			endwin();
			delete_graph(graph);
			exit(0);
	}
}

void draw_game_over(WINDOW *win)
{
	wattr_on(win, COLOR_PAIR(PAIR_GAME_OVER), NULL);
	for(int y=0;y<HEIGHT_GAME_OVER;y++)
	{
		mvwprintw(win, y, 0, game_over[y]);
	}
	wattr_off(win, COLOR_PAIR(PAIR_GAME_OVER), NULL);
	wrefresh(win);
	usleep(2*1000000);
}

void draw_help(WINDOW *win)
{
	wattr_on(win, COLOR_PAIR(PAIR_HELP), NULL);
	for(int y=0;y<HEIGHT_HELP;y++)
	{
		mvwprintw(win, y, 0, help_template[y]);
	}
	wattr_off(win, COLOR_PAIR(PAIR_HELP), NULL);
	wrefresh(win);
}
