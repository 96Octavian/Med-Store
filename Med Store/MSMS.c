#include "ncurses.h"
#include "unistd.h"

void main() {
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	cbreak();
	refresh();
	WINDOW *top_box, *main_box;
	top_box = newwin(5, COLS, 0, 0);
	box(top_box, 0, 0);
	wrefresh(top_box);
	main_box = newwin(LINES - 6, COLS, 6, 0);
	box(main_box, 0, 0);
	wrefresh(top_box);
	wrefresh(main_box);
	sleep(2);
	endwin();
}