/* Linux implementation of a Windows project
** Missing: t()/display_date_time function */
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
		mvaddstr(i, COLS-1, "#");
	}
	for(i=COLS-1; i>0; i--){
		mvaddstr(4, i, "#");
	}
	for(i=4; i>0; i--){
		mvaddstr(i, 0, "#");
	}

	refresh();
}

void main_box(){
	move(5, 0);
	clrtobot();
	int i;
	for(i=0; i<COLS; i++){
		mvaddstr(5, i, "#");
	}
	for(i=6; i<LINES-1; i++){
		mvaddstr(i, COLS-1, "#");
	}
	for(i=COLS-1; i>0; i--){
		mvaddstr(LINES-1, i, "#");
	}
	for(i=LINES-1; i>0; i--){
		mvaddstr(i, 0, "#");
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
		mvaddstr(i, COLS-1, "#");
	}
	for(i=COLS-1; i>0; i--){
		mvaddstr(LINES-1, i, "#");
	}
	for(i=LINES-1; i>0; i--){
		mvaddstr(i, 0, "#");
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
	refresh();
	sleep(0.5);
	mvprintw(LINES-2, COLS-1-1-strlen("Press first character for further Menu"), "Press first character for further Menu");
	refresh();
}

void main_menu(){
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
	}

	clear();
	mvprintw(LINES/2, COLS/2 - strlen("Exiting...")/2, "Exiting...");
	refresh();
	sleep(1);

	endwin();
	
	return(0);
}