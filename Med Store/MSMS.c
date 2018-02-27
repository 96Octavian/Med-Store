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

int current_window = 1;

void main_menu_builder();
void exit_builder();
void supplier_menu_builder();
void customer_menu_builder();
void medicine_menu_builder();

// SIGWINCH is called when the window is resized.
void main_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	initscr();
	clear();
	refresh();

	signal(SIGWINCH, main_winch);
}

void main_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	initscr();
	clear();
	refresh();

	signal(SIGWINCH, main_menu_winch);
	main_menu_builder();
}

void supplier_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	initscr();
	clear();
	refresh();

	signal(SIGWINCH, supplier_menu_winch);
	supplier_menu_builder();
}

void customer_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	initscr();
	clear();
	refresh();

	signal(SIGWINCH, customer_menu_winch);
	customer_menu_builder();
}

void medicine_menu_winch(int sig) {
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	initscr();
	clear();
	refresh();

	signal(SIGWINCH, medicine_menu_winch);
	medicine_menu_builder();
}

void exit_winch(int sig){
	signal(SIGWINCH, SIG_IGN);

	// Reinitialize the window to update data structures.
	endwin();
	initscr();
	clear();
	refresh();

	signal(SIGWINCH, exit_winch);
	exit_builder();
}

void top_box() {
	int i;
	for(i=0; i<5; i++){
		move(i, 0);
		clrtoeol();
	}
	for(i=0; i<COLS-1; i++){
		mvprintw(0, i, "#");
	}
	for(i=0; i<5; i++){
		mvprintw(i, COLS-1, "#");
	}
	for(i=COLS-1; i>0; i--){
		mvprintw(4, i, "#");
	}
	for(i=4; i>0; i--){
		mvprintw(i, 0, "#");
	}

	refresh();
}

void main_box(){
	move(5, 0);
	clrtobot();
	int i;
	for(i=0; i<COLS; i++){
		mvprintw(5, i, "#");
	}
	for(i=6; i<LINES-1; i++){
		mvprintw(i, COLS-1, "#");
	}
	for(i=COLS-1; i>0; i--){
		mvprintw(LINES-1, i, "#");
	}
	for(i=LINES-1; i>0; i--){
		mvprintw(i, 0, "#");
	}
	refresh();
}

void exit_builder(){
	signal(SIGWINCH, exit_winch);
	clear();

	int i;
	for(i=0; i<COLS-1; i++){
		mvprintw(0, i, "#");
	}
	for(i=0; i<LINES-1; i++){
		mvprintw(i, COLS-1, "#");
	}
	for(i=COLS-1; i>0; i--){
		mvprintw(LINES-1, i, "#");
	}
	for(i=LINES-1; i>0; i--){
		mvprintw(i, 0, "#");
	}
	refresh();

	mvprintw(LINES/2, COLS/2 - strlen("Do you want to exit now (Y/N)?")/2, "Do you want to exit now (Y/N)?");
	refresh();
}

int exiter(){
	exit_builder();
	char ch;
	while((ch = toupper((getchar()))) != 'Y' && ch != 'N'){
		mvprintw(LINES/2+1, COLS/2 - strlen("Press only Y or N")/2, "Press only Y or N");
		refresh();
	}
	if (ch == 'Y'){
		current_window = 0;
	}
	return current_window;
}

void main_menu_builder(){
	top_box();
	main_box();
	mvprintw(2, COLS/2 - strlen("Supplier info    Customer info    Medicine    Report    Bill    About    Exit")/2, "Supplier info    Customer info    Medicine    Report    Bill    About    Exit");
	mvprintw(LINES/2, COLS/2 - strlen("Welcome to Medical Store")/2, "Welcome to Medical Store");
	mvprintw(LINES / 2 + 1, COLS / 2 - strlen("Management System") / 2, "Management System");
	refresh();
	sleep(0.5);
	mvprintw(LINES-2, COLS-1-1-strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void main_menu(){
	/* current_windows == 1 */
	signal(SIGWINCH, main_menu_winch);
	main_menu_builder();
	char ch;
	while((ch = toupper(getchar())) != 27){
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
			if(exiter()){
				main_menu_builder();
			}
			else{
				return;
			}
			break;
		default:
			mvprintw(LINES-2, COLS-1-1-strlen("Plese Enter right character ONLY (S,C,M,R,B,A)"), "Plese Enter right character ONLY (S,C,M,R,B,A)");
			refresh();
			break;
		}
	}
	current_window=0;
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

int main(int argc, char *argv[]) {
	initscr();
	refresh();
	// COLS/LINES are now set

	signal(SIGWINCH, main_winch);
	clear();
	
	while(current_window != 0){
		if(current_window == 1){
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
	}

	clear();
	mvprintw(LINES/2, COLS/2 - strlen("Exiting...")/2, "Exiting...");
	refresh();
	sleep(1);

	endwin();
	
	return(0);
}