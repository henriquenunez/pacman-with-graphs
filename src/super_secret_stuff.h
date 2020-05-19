//Easter egg.

#define WIDTH_EASTER_EGG 26
#define HEIGHT_EASTER_EGG 8

char easter_egg_template[HEIGHT_EASTER_EGG][WIDTH_EASTER_EGG] = {
{" __      _______ __  __ _ "},
{" \\ \\    / /_   _|  \\/  | |"},
{"  \\ \\  / /  | | | \\  / | |"},
{"   \\ \\/ /   | | | |\\/| | |"},
{"    \\  /   _| |_| |  | |_|"},
{"     \\/   |_____|_|  |_(_)"},
{"                          "},
{"                          "},
};



void draw_easter_egg(WINDOW *win)
{
	wattr_on(win, COLOR_PAIR(PAIR_GAME_OVER), NULL);
	for(int y=0;y<HEIGHT_EASTER_EGG;y++)
	{
		mvwprintw(win, y, 0, easter_egg_template[y]);
	}
	wattr_off(win, COLOR_PAIR(PAIR_GAME_OVER), NULL);
	wrefresh(win);
	usleep(2*1000000);
}

