#include <string.h>
#include <ctype.h>
#include "ncurses.h"
#include "unistd.h"

int exiter() {
	WINDOW *full = newwin(LINES, COLS, 0, 0);
	wclear(full);
	box(full, 0, 0);
	mvwprintw(full, LINES / 2, COLS / 2 - strlen("Do you want to exit now (Y/N)?") / 2, "Do you want to exit now (Y/N)?");
	wrefresh(full);

	char ch;
	while ((ch = toupper((getchar()))) != 'Y' && ch != 'N') {
		mvwprintw(full, LINES / 2 + 1, COLS / 2 - strlen("Press only Y or N") / 2, "Press only Y or N");
		wrefresh(full);
	}
	delwin(full);
	return ch;
}

void supplier_menu() {
	return;
}
void customer_menu() {
	return;
}
void medicine_menu() {
	return;
}
void report_menu() {
	return;
}
void bill_menu() {
	return;
}
void about() {
	return;
}

void main() {
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	cbreak();
	refresh();
	WINDOW *top_box, *main_box;
	char *menus = "Supplier info    Customer info    Medicine    Report    Bill    About    Exit";
	char *wrong_char = "Plese Enter right character ONLY (S,C,M,R,B,A)";
	int ch, i = 0;

	top_box = subwin(stdscr, 5, COLS, 0, 0);
	box(top_box, 0, 0);
	main_box = subwin(stdscr, LINES - 6, COLS, 6, 0);
	box(main_box, 0, 0);
	mvwprintw(top_box, 2, COLS / 2 - strlen(menus) / 2, menus);
	mvwprintw(main_box, LINES / 2 - 6, COLS / 2 - strlen("Welcome to Medical Store") / 2, "Welcome to Medical Store");
	mvwprintw(main_box, LINES / 2 - 5, COLS / 2 - strlen("Management System") / 2, "Management System");
	mvwprintw(main_box, LINES - 2, COLS - 1 - 1 - strlen("Press first character for further Menu"), "Press first character for further Menu");
	wnoutrefresh(top_box);
	wnoutrefresh(main_box);
	doupdate();
	while ((ch = toupper(getchar())) != 27) {
		if (ch == 'S') {
			supplier_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'C') {
			customer_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'M') {
			medicine_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'R') {
			report_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'B') {
			bill_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'A') {
			about();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'E') {
			if (exiter() == 'Y') {
				break;
			}
			else {
				touchwin(stdscr);
			}
		}
		else {
			mvwprintw(main_box, LINES - 2, COLS - 1 - 1 - strlen(wrong_char), wrong_char);
		}
		refresh();
	}
	clear();
	mvwprintw(stdscr, LINES / 2, COLS / 2 - strlen("Exiting...") / 2, "Exiting...");
	wrefresh(stdscr);

	delwin(top_box);
	delwin(main_box);
	sleep(2);
	endwin();
	return;
}