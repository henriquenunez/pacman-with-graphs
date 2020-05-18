#include <curses.h>
#include <unistd.h>

#include "graph.h"

#include <stdio.h>

#define SIZE 5

void drawGraph(WINDOW *win);

int main(int argc, char *argv[]) {
	//--- Inicializa a janela ---//
	initscr();
	noecho();
	curs_set(FALSE);

	//--- Cria janela do jogo ---//
	int maxX=0, maxY=0;
	// Recebe tamanho da janela
	getmaxyx(stdscr, maxY, maxX);
	// Cria janela (posY, posX, offsetY, offsetX)
	WINDOW *game  = newwin(SIZE, SIZE, maxY/2-SIZE/2, maxX/2-SIZE/2);
	refresh();

	// Desenha grafo
	drawGraph(game);

	GRAPH* the_graph = create_graph(10,10);
	printf("oi!");
	delete_graph(the_graph);

	usleep(1*1000000);	
	// Destroi a janela
	endwin();

	return 0;
}

void drawGraph(WINDOW *win)
{
	int x,y;
	// Limpa janela
	wclear(win);

	// Desenha grafo no centro da janela
	for(x=0;x<SIZE;x++)
	{
		for(y=0;y<SIZE;y++)
		{
			mvwprintw(win, y, x, "0");
		}
	}
	
	// Atualiza a janela
	wrefresh(win);
}
