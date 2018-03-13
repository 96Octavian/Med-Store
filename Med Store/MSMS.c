#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include "ncurses.h"
#include "unistd.h"
#include "useful.h"

struct bills {
	char billno[6];
	char cname[30];
	char medinumber[6];
	char mediname[30];
	int medi_qty;
	float medi_rate;
	int day;
	int month;
	int year;
};

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
	wclear(full);
	delwin(full);
	return ch;
}

void supplier_menu() {
	return;
}
int customer_menu() {
	return 1;
}
void medicine_menu() {
	return;
}
void report_menu() {
	return;
}

void by_billno(char *query) {
	int ch, i = 11;
	char *buf;
	struct bills bil;

	WINDOW *full_box = newwin(LINES, COLS, 0, 0);
	FILE *ptrbill = fopen("dbbill.dat", "r");
	if (!ptrbill) {
		box(full_box, 0, 0);
		mvwprintw(full_box, LINES / 2, COLS / 2 - strlen("Cannot open Bill file!") / 2, "Cannot open Bill file!");
		wrefresh(full_box);
		sleep(2);
		wclear(full_box);
		delwin(full_box);
		return;
	}
	box(full_box, 0, 0);
	mvwprintw(full_box, 3, 4, "Bill n: %s", query);
	mvwprintw(full_box, 3, COLS - 1 - 16 - 16, "Date:");
	mvwprintw(full_box, 5, 4, "Customer name:");
	mvwprintw(full_box, 8, 4, "Sr. No              Medicine Name              Qty              Rate              Subtotal");
	wmove(full_box, 9, 1);
	whline(full_box, 0, COLS - 2);
	wrefresh(full_box);

	while (!(reader(ptrbill, &buf))) {
		sscanf(buf, "%[^_]_%[^_]_%[^_]_%[^_]_%d_%f_%d_%d_%d", bil.billno, bil.cname, bil.medinumber, bil.mediname, &(bil.medi_qty), &(bil.medi_rate), &(bil.day), &(bil.month), &(bil.year));
		if (strcmp(query, bil.billno) == 0) {
			mvwprintw(full_box, i, 4, "%s", bil.medinumber);
			mvwprintw(full_box, i, 24, "%s", bil.mediname);
			mvwprintw(full_box, i, 51, "%d", bil.medi_qty);
			mvwprintw(full_box, i, 68, "%.2f", bil.medi_rate);
			mvwprintw(full_box, i, 86, "%.2f", bil.medi_rate * bil.medi_qty);
			i = i + 2;
			wrefresh(full_box);
		}
		free(buf);
	}
	mvwprintw(full_box, 3, COLS - 1 - 16 - 10, "%d/%d/%d", bil.day, bil.month, bil.year);
	mvwprintw(full_box, 5, 19, "%s", bil.cname);
	wrefresh(full_box);

	while ((ch = getch()) != 27);
	//	free(bil);
	query[0] = '\0';
	wclear(full_box);
	delwin(full_box);
	return;
}
void search_bill() {
	WINDOW *full_box = newwin(LINES, COLS, 0, 0);
	curs_set(1);
	box(full_box, 0, 0);
	mvwprintw(full_box, 6, 14, "Search by");
	mvwprintw(full_box, 6, 28, "Bill number:");
	mvwprintw(full_box, 9, 28, "Day:");
	mvwprintw(full_box, 12, 28, "Client name:");
	mvwprintw(full_box, LINES - 2, COLS - 1 - 1 - strlen("[ESC] to get back"), "[ESC] to get back");

	char query[30];
	int y = 6, x = 42;
	int i = 0;
	int ch, day, month, year;
	query[i] = '\0';
	wmove(full_box, y, x);
	wrefresh(full_box);

	while ((ch = getch()) != 27) {
		getyx(full_box, y, x);

		if (ch == 10) {
			if (strlen(query) == 0) {
				mvwprintw(full_box, 15, 42, "Search field is empty!");
				wmove(full_box, y, x);
			}
			else if (y == 6 && strlen(query) > 6) {
				mvwprintw(full_box, 15, 42, "Bill number too long");
				wmove(full_box, y, x);
			}
			else if (y == 9 && sscanf(query, "%d/%d/%d", &day, &month, &year) != 3) {
				mvwprintw(full_box, 15, 42, "Wrong date format (dd/mm/yyyy)");
				wmove(full_box, y, x);
			}
			else if (y == 12 && strlen(query) > 29) {
				mvwprintw(full_box, 15, 42, "Name too long");
				wmove(full_box, y, x);
			}
			else {
				break;
			}
		}
		else if (isalpha(ch) || isdigit(ch) || ch == ' ' || ch == '/') {
			query[i] = ch;
			i++;
			query[i] = '\0';
			waddch(full_box, ch);

			// This bit removes the "Empty field" warning if set
			getyx(full_box, y, x);
			mvwprintw(full_box, 15, 42, "                              ");
			wmove(full_box, y, x);

		}
		else {
			if (ch == KEY_UP) {
				if (y == 6 || x > 42) {
					continue;
				}
				wmove(full_box, y - 3, x);
			}
			else if (ch == KEY_DOWN) {
				if (y == 12 || x > 42) {
					continue;
				}
				wmove(full_box, y + 3, x);
			}
			else if (ch == KEY_BACKSPACE) {
				if (x == 42) {
					continue;
				}
				wmove(full_box, y, x - 1);
				waddch(full_box, ' ');
				wmove(full_box, y, x - 1);
				i--;
				query[i] = '\0';
			}
		}
		wrefresh(full_box);
	}
	if (ch == 27) {
		query[0] = '\0';
		wclear(full_box);
		delwin(full_box);
		curs_set(0);
		return;
	}
	if (y == 6) {
		curs_set(0);
		by_billno(query);
	}
	query[0] = '\0';
	wclear(full_box);
	delwin(full_box);
	curs_set(0);
	return;
}
int bill_menu() {
	WINDOW *bill, *top_box, *main_box;
	char *menus = "New    Search    Main Menu    Exit";
	char *wrong_char = "Plese Enter right character ONLY (N,S,M,E)";
	int ch;

	bill = newwin(LINES, COLS, 0, 0);
	top_box = subwin(bill, 5, COLS, 0, 0);
	box(top_box, 0, 0);
	main_box = subwin(bill, LINES - 6, COLS, 6, 0);
	box(main_box, 0, 0);

	mvwprintw(top_box, 2, COLS / 2 - strlen(menus) / 2, menus);
	mvwprintw(main_box, LINES / 2 - 6, COLS / 2 - strlen("Bill Menu") / 2, "Bill Menu");
	wnoutrefresh(top_box);
	wnoutrefresh(main_box);
	doupdate();

	while ((ch = toupper(getchar())) || ch == 0) {
		if (ch == 'N') {
			supplier_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'S') {
			search_bill();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'M') {
			wclear(bill);
			delwin(top_box);
			delwin(main_box);
			delwin(bill);
			return 1;
		}
		else if (ch == 'E') {
			if (exiter() == 'Y') {
				wclear(bill);
				delwin(top_box);
				delwin(main_box);
				delwin(bill);
				return 0;
			}
			else {
				touchwin(bill);
			}
		}
		else {
			mvwprintw(main_box, LINES - 2 - 6, COLS - 1 - 1 - strlen(wrong_char), wrong_char);
			wrefresh(main_box);
		}
		wrefresh(bill);
	}
}

void about() {
	return;
}

void main() {
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	cbreak();
	curs_set(0);
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
	while ((ch = toupper(getchar())) || ch == 0) {
		if (ch == 'S') {
			supplier_menu();
			touchwin(top_box);
			touchwin(main_box);
		}
		else if (ch == 'C') {
			if (!(customer_menu())) {
				break;
			}
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
			if (!(bill_menu())) {
				break;
			}
			touchwin(stdscr);
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
			mvwprintw(main_box, LINES - 2 - 6, COLS - 1 - 1 - strlen(wrong_char), wrong_char);
			wrefresh(main_box);
		}
		refresh();
	}
	clear();
	mvwprintw(stdscr, LINES / 2, COLS / 2 - strlen("Exiting...") / 2, "Exiting...");
	wrefresh(stdscr);

	delwin(top_box);
	delwin(main_box);
	sleep(0.5);
	endwin();
	return;
}