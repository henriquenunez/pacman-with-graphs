#include <curses.h>
#include <unistd.h>
#include "graph.c"

#include "graph.h"

#include <stdio.h>

#define SIZE 5

void drawGraph(WINDOW *win);

int main(int argc, char *argv[]) {
	//--- Initialize curses ---//
	initscr();
	noecho();
	curs_set(FALSE);

	//--- Create game window ---//
	int maxX=0, maxY=0;
	// Get window size 
	getmaxyx(stdscr, maxY, maxX);
	// Create window (posY, posX, offsetY, offsetX)
	WINDOW *game  = newwin(SIZE, SIZE, maxY/2-SIZE/2, maxX/2-SIZE/2);
	refresh();

	//--- Create graph ---//
	GRAPH *graph = create_graph(SIZE, SIZE);

<<<<<<< HEAD
	//--- Game loop ---//
	drawGraph(game);
	usleep(1*1000000);	

	// Destroy curses window
=======
	GRAPH* the_graph = create_graph(10,10);
	printf("oi!");
	delete_graph(the_graph);

	usleep(1*1000000);
	// Destroi a janela
>>>>>>> master
	endwin();
	delete_graph(graph);

	return 0;
}

void drawGraph(WINDOW *win)
{
	int x,y;
	// Clear window
	wclear(win);

	// Draw board
	for(x=0;x<SIZE;x++)
	{
		for(y=0;y<SIZE;y++)
		{
			mvwprintw(win, y, x, "0");
		}
	}
	
	// Refresh window 
	wrefresh(win);
}
