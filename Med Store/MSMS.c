/* Linux implementation of a Windows project
** Missing:	t()/display_date_time
**			remainder() to show ending medicines
*/
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "unistd.h"
#include "ncurses.h"
#include "useful.h"

int current_window = 1;

WINDOW *current;

struct bill {
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
struct bill bil;
char query[30];
int y, x;


void main_menu_builder();
void exit_builder();
void supplier_menu_builder();
void customer_menu_builder();
void medicine_menu_builder();
void report_menu_builder();
void about_menu_builder();
void bill_menu_builder();
void search_bill_builder();
void search_by_billno();

// SIGWINCH is called when the window is resized.
void main_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, main_winch);
}

void main_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, main_menu_winch);
	main_menu_builder();
}

void supplier_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, supplier_menu_winch);
	supplier_menu_builder();
}

void customer_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, customer_menu_winch);
	customer_menu_builder();
}

void medicine_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, medicine_menu_winch);
	medicine_menu_builder();
}

void report_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, report_menu_winch);
	report_menu_builder();
}

void about_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, about_menu_winch);
	about_menu_builder();
}

void bill_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, bill_menu_winch);
	bill_menu_builder();
}

void search_bill_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, bill_menu_winch);
	search_bill_builder();
}

void exit_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	current = initscr(); noecho(); keypad(current, TRUE);
	clear();
	refresh();

	signal(SIGWINCH, exit_winch);
	exit_builder();
}

void top_box() {
	int i;
	for (i = 0; i<5; i++) {
		move(i, 0);
		clrtoeol();
	}
	for (i = 0; i<COLS - 1; i++) {
		mvprintw(0, i, "#");
	}
	for (i = 0; i<5; i++) {
		mvprintw(i, COLS - 1, "#");
	}
	for (i = COLS - 1; i>0; i--) {
		mvprintw(4, i, "#");
	}
	for (i = 4; i>0; i--) {
		mvprintw(i, 0, "#");
	}

	refresh();
}

void main_box() {
	move(5, 0);
	clrtobot();
	int i;
	for (i = 0; i<COLS; i++) {
		mvprintw(5, i, "#");
	}
	for (i = 6; i<LINES - 1; i++) {
		mvprintw(i, COLS - 1, "#");
	}
	for (i = COLS - 1; i>0; i--) {
		mvprintw(LINES - 1, i, "#");
	}
	for (i = LINES - 1; i>0; i--) {
		mvprintw(i, 0, "#");
	}
	refresh();
}

void full_box() {
	clear();
	int i;
	for (i = 0; i<COLS - 1; i++) {
		mvprintw(0, i, "#");
	}
	for (i = 0; i<LINES - 1; i++) {
		mvprintw(i, COLS - 1, "#");
	}
	for (i = COLS - 1; i>0; i--) {
		mvprintw(LINES - 1, i, "#");
	}
	for (i = LINES - 1; i>0; i--) {
		mvprintw(i, 0, "#");
	}
	refresh();
}

void exit_builder() {
	signal(SIGWINCH, exit_winch);
	clear();

	int i;
	for (i = 0; i<COLS - 1; i++) {
		mvprintw(0, i, "#");
	}
	for (i = 0; i<LINES - 1; i++) {
		mvprintw(i, COLS - 1, "#");
	}
	for (i = COLS - 1; i>0; i--) {
		mvprintw(LINES - 1, i, "#");
	}
	for (i = LINES - 1; i>0; i--) {
		mvprintw(i, 0, "#");
	}
	refresh();

	mvprintw(LINES / 2, COLS / 2 - strlen("Do you want to exit now (Y/N)?") / 2, "Do you want to exit now (Y/N)?");
	refresh();
}

int exiter() {
	exit_builder();
	char ch;
	while ((ch = toupper((getchar()))) != 'Y' && ch != 'N') {
		mvprintw(LINES / 2 + 1, COLS / 2 - strlen("Press only Y or N") / 2, "Press only Y or N");
		refresh();
	}
	if (ch == 'Y') {
		current_window = 0;
	}
	return current_window;
}

void main_menu_builder() {
	top_box();
	main_box();
	mvprintw(2, COLS / 2 - strlen("Supplier info    Customer info    Medicine    Report    Bill    About    Exit") / 2, "Supplier info    Customer info    Medicine    Report    Bill    About    Exit");
	mvprintw(LINES / 2, COLS / 2 - strlen("Welcome to Medical Store") / 2, "Welcome to Medical Store");
	mvprintw(LINES / 2 + 1, COLS / 2 - strlen("Management System") / 2, "Management System");
	refresh();
	sleep(0.5);
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void main_menu() {
	/* current_windows == 1 */
	signal(SIGWINCH, main_menu_winch);
	main_menu_builder();
	char ch;
	while ((ch = toupper(getchar())) != 27) {
		switch (ch) {
		case 'S':
			current_window = 2;
			return;
		case 'C':
			current_window = 3;
			return;
		case 'M':
			current_window = 4;
			return;
		case 'R':
			current_window = 5;
			return;
		case 'B':
			current_window = 6;
			return;
		case 'A':
			current_window = 7;
			return;
		case 'E':
			if (exiter()) {
				main_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese Enter right character ONLY (S,C,M,R,B,A)"), "Plese Enter right character ONLY (S,C,M,R,B,A)");
			refresh();
			break;
		}
	}
	current_window = 0;
}

void supplier_menu_builder() {
	clear();
	top_box();
	main_box();
	mvprintw(2, COLS / 2 - strlen("Add    Update    List    Search    Main Menu    Exit") / 2, "Add    Update    List    Search    Main Menu    Exit");
	mvprintw(LINES / 2, COLS / 2 - strlen("Supplier Menu") / 2, "Supplier Menu");
	refresh();
	sleep(0.5);
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void supplier_menu() {
	/* current_window == 2 */
	signal(SIGWINCH, supplier_menu_winch);
	supplier_menu_builder();
	char ch;
	while (ch = toupper(getchar())) {
		switch (ch) {
		case 'A':
			current_window = 21;
			return;
		case 'U':
			current_window = 22;
			return;
		case 'L':
			current_window = 23;
			return;
		case 'S':
			current_window = 24;
			return;
		case 'M':
			current_window = 1;
			return;
		case 'E':
			if (exiter()) {
				supplier_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese Enter right character ONLY (A,U,L,S,M,E)"), "Plese Enter right character ONLY (A,U,L,S,M,E)");
			refresh();
			break;
		}
	}
}

void customer_menu_builder() {
	clear();
	top_box();
	main_box();
	mvprintw(2, COLS / 2 - strlen("Add    Update    List    Search    Main Menu    Exit") / 2, "Add    Update    List    Search    Main Menu    Exit");
	mvprintw(LINES / 2, COLS / 2 - strlen("Customer Menu") / 2, "Customer Menu");
	refresh();
	sleep(0.5);
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void customer_menu() {
	/* current_window == 3 */
	signal(SIGWINCH, customer_menu_winch);
	customer_menu_builder();
	char ch;
	while (ch = toupper(getchar())) {
		switch (ch) {
		case 'A':
			current_window = 31;
			return;
		case 'U':
			current_window = 32;
			return;
		case 'L':
			current_window = 33;
			return;
		case 'S':
			current_window = 34;
			return;
		case 'M':
			current_window = 1;
			return;
		case 'E':
			if (exiter()) {
				customer_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese Enter right character ONLY (A,U,L,S,M,E)"), "Plese Enter right character ONLY (A,U,L,S,M,E)");
			refresh();
			break;
		}
	}
}

void medicine_menu_builder() {
	clear();
	top_box();
	main_box();
	mvprintw(2, COLS / 2 - strlen("Purchase    Sell    In Stock    List    Main    Exit") / 2, "Purchase    Examination    In Stock    Search    Main    Exit");
	mvprintw(LINES / 2, COLS / 2 - strlen("Medicine Menu") / 2, "Medicine Menu");
	refresh();
	sleep(0.5);
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void medicine_menu() {
	/* current_window == 4 */
	signal(SIGWINCH, medicine_menu_winch);
	medicine_menu_builder();
	char ch;
	while (ch = toupper(getchar())) {
		switch (ch) {
		case 'P':
			current_window = 41;
			return;
		case 'S':
			current_window = 42;
			return;
		case 'I':
			current_window = 43;
			return;
		case 'L':
			current_window = 44;
			return;
		case 'M':
			current_window = 1;
			return;
		case 'E':
			if (exiter()) {
				medicine_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese Enter right character ONLY (P,S,I,L,M,E)"), "Plese Enter right character ONLY (P,S,I,L,M,E)");
			refresh();
			break;
		}
	}
}

void report_menu_builder() {
	clear();
	top_box();
	main_box();
	mvprintw(2, COLS / 2 - strlen("Purchase    Sale    Balance    Daily Report    Main menu    Exit") / 2, "Purchase    Sale    Balance    Daily Report    Main menu    Exit");
	mvprintw(LINES / 2, COLS / 2 - strlen("Report Menu") / 2, "Report Menu");
	refresh();
	sleep(0.5);
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void report_menu() {
	/* current_window == 5 */
	signal(SIGWINCH, report_menu_winch);
	report_menu_builder();
	char ch;
	while (ch = toupper(getchar())) {
		switch (ch) {
		case 'P':
			current_window = 51;
			return;
		case 'S':
			current_window = 52;
			return;
		case 'B':
			current_window = 53;
			return;
		case 'D':
			current_window = 54;
			return;
		case 'M':
			current_window = 1;
			return;
		case 'E':
			if (exiter()) {
				medicine_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese Enter right character ONLY (P,S,B,D,M,E)"), "Plese Enter right character ONLY (P,S,B,D,M,E)");
			refresh();
			break;
		}
	}
}

void about_menu_builder() {
	full_box();
	mvprintw(LINES / 2 - 3, COLS / 2 - strlen("***** MEDICAL STORE ****") / 2, "***** MEDICAL STORE ****");
	mvprintw(LINES / 2 - 1, COLS / 2 - strlen("This Project is about Medical Store") / 2, "This Project is about Medical Store");
	mvprintw(LINES / 2, COLS / 2 - strlen("=> In this Project we can add medicine, customer, supplier details <=") / 2, "=> In this Project we can add medicine, customer, supplier details <=");
	mvprintw(LINES / 2 + 1, COLS / 2 - strlen("=> We can modify & delete existing Records <=") / 2, "=> We can modifed & delete existing Records <=");
	mvprintw(LINES / 2 + 2, COLS / 2 - strlen("=> We can also search medicine, customer, supplier details <=") / 2, "=> We can also search medicine, customer, supplier details <=");
	refresh();
	sleep(0.5);
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Press M or E"), "Press M or E");
	refresh();
}

void about_menu() {
	/* current_window == 7 */
	signal(SIGWINCH, about_menu_winch);
	about_menu_builder();

	char ch;
	while (ch = toupper(getchar())) {
		switch (ch) {
		case 'M':
			current_window = 1;
			return;
		case 'E':
			if (exiter()) {
				medicine_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese press only M or E"), "Plese press only M or E");
			refresh();
			break;
		}
	}
}

void bill_menu_builder() {
	clear();
	top_box();
	main_box();
	refresh();

	mvprintw(2, COLS / 2 - strlen("New    Search    Main Menu    Exit") / 2, "New    Search    Main Menu    Exit");
	mvprintw(LINES / 2, COLS / 2 - strlen("Bill Menu") / 2, "Bill Menu");
	refresh();
	mvprintw(LINES - 2, COLS - 2 - strlen("Press N or S"), "Press N or S");
	refresh();
}

void bill_menu() {
	/* current_window == 6 */
	signal(SIGWINCH, bill_menu_winch);
	bill_menu_builder();

	char ch;
	while (ch = toupper(getchar())) {
		switch (ch) {
		case 'N':
			current_window = 61;
			return;
		case 'S':
			current_window = 62;
			return;
		case 'M':
			current_window = 1;
			return;
		case 'E':
			if (exiter()) {
				bill_menu_builder();
			}
			else {
				return;
			}
			break;
		default:
			mvprintw(LINES - 2, COLS - 1 - 1 - strlen("Plese press only M or E"), "Plese press only M or E");
			refresh();
			break;
		}
	}
}

void search_bill_builder() {
	full_box();
	mvprintw(6, 14, "Search by");
	mvprintw(6, 28, "Bill number:");
	mvprintw(9, 28, "Day:");
	mvprintw(12, 28, "Client name:");
	mvprintw(LINES - 2, COLS - 1 - 1 - strlen("[ESC] to get back"), "[ESC] to get back");
	mvprintw(y, 42, query);
	move(y, x);
	refresh();
}

void search_bill() { // Called void bill() in original file

	y = 6; x = 42;
	signal(SIGWINCH, search_bill_winch);
	search_bill_builder();
	int i = 0;

	int ch, day, month, year;
	query[i] = '\0';
	while ((ch = getch()) != 27) {
		getyx(current, y, x);

		if (ch == 10) {
			if (strlen(query) == 0) {
				mvprintw(15, 42, "Search field is empty!");
				move(y, x);
				refresh();
				continue;
			}
			else if (y == 6 && strlen(query) > 5) {
				mvprintw(15, 42, "Bill number too long");
				move(y, x);
				refresh();
				continue;
			}
			else if (y == 9 && sscanf(query, "%d/%d/%d", &day, &month, &year) != 3) {
				mvprintw(15, 42, "Wrong date format");
				move(y, x);
				refresh();
				continue;
			}
			else if (y == 12 && strlen(query) > 29) {
				mvprintw(15, 42, "Name too long");
				move(y, x);
				refresh();
				continue;
			}
			break;
		}
		if (isalpha(ch) || isdigit(ch) || ch == ' ' || ch == '/') {
			query[i] = ch;
			i++;
			query[i] = '\0';
			addch(ch);

			move(15, 42);
			clrtoeol();
			mvprintw(15, COLS - 1, "#");
			move(y, x + 1);

		}
		else {
			if (ch == KEY_UP) {
				move(y, x);
				refresh();
				if (y == 6 || x > 42) {
					continue;
				}
				move(y - 3, x);
			}
			else if (ch == KEY_DOWN) {
				move(y, x);
				refresh();
				if (y == 12 || x > 42) {
					continue;
				}
				move(y + 3, x);
			}
			else if (ch == KEY_BACKSPACE) {
				move(y, x);
				refresh();
				if (x == 42) {
					continue;
				}
				move(y, x - 1);
				addch(' ');
				move(y, x - 1);
				i--;
				query[i] = '\0';
			}
		}
	}
	if (ch == 27) {
		current_window = 6;
		return;
	}
	if (y == 6) {
		search_by_billno();
	}
	current_window = 6;
	return;
}
void search_by_billno() {
	signal(SIGWINCH, SIG_IGN);
	int ch, i;
	FILE *ptrbill = fopen("dbbill.dat", "r");
	if (!ptrbill) {
		clear();
		full_box();
		mvprintw(LINES / 2, COLS / 2 - strlen("Cannot open Bill file!") / 2, "Cannot open Bill file!");
		current_window = 6;
		refresh();
		sleep(3);
		return;
	}
	clear();
	full_box();
	mvprintw(3, 4, "Bill n: %s", query);
	mvprintw(3, COLS - 1 - 16 - 16, "Date:");
	mvprintw(5, 4, "Customer name:");
	mvprintw(8, 4, "Sr. No              Medicine Name              Qty              Rate              Subtotal");
	move(9, 2);
	for (i = 2; i < COLS - 2; i++) {
		addch('-');
	}
	refresh();
	i = 11;
	char *buf;
	while (!(reader(ptrbill, &buf))) {
		sscanf(buf, "%[^_]_%[^_]_%[^_]_%[^_]_%d_%f_%d_%d_%d", bil.billno, bil.cname, bil.medinumber, bil.mediname, &(bil.medi_qty), &(bil.medi_rate), &(bil.day), &(bil.month), &(bil.year));
		if (strcmp(query, bil.billno) == 0) {
			mvprintw(i, 4, "%s", bil.medinumber);
			mvprintw(i, 24, "%s", bil.mediname);
			mvprintw(i, 51, "%d", bil.medi_qty);
			mvprintw(i, 68, "%.2f", bil.medi_rate);
			mvprintw(i, 86, "%.2f", bil.medi_rate * bil.medi_qty);
			i = i + 2;
			refresh();
		}
		free(buf);
	}
	query[0] = '\0';
	while ((ch = getch()) != 27) {}
}

int main(int argc, char *argv[]) {
	current = initscr(); noecho(); keypad(current, TRUE);
	refresh();
	// COLS/LINES are now set

	signal(SIGWINCH, main_winch);
	clear();

	while (current_window != 0) {
		if (current_window == 1) {
			main_menu();
		}
		else if (current_window == 2) {
			supplier_menu();
		}
		else if (current_window == 3) {
			customer_menu();
		}
		else if (current_window == 4) {
			medicine_menu();
		}
		else if (current_window == 5) {
			report_menu();
		}
		else if (current_window == 6) {
			bill_menu();
		}
		else if (current_window == 62) {
			search_bill();
		}
		else if (current_window == 7) {
			about_menu();
		}
	}

	clear();
	mvprintw(LINES / 2, COLS / 2 - strlen("Exiting...") / 2, "Exiting...");
	refresh();
	sleep(1);

	endwin();

	return(0);
}