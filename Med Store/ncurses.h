#include <stdarg.h>

#include <varargs.h>

#define COLS	0

#define LINES	0

typedef WINDOW;

int move(int y, int x);

int wmove(WINDOW *win, int y, int x);

int addstr(const char *str);

int addnstr(const char *str, int n);

int waddstr(WINDOW *win, const char *str);

int waddnstr(WINDOW *win, const char *str, int n);

int mvaddstr(int y, int x, const char *str);

int mvaddnstr(int y, int x, const char *str, int n);

int mvwaddstr(WINDOW *win, int y, int x, const char *str);

int mvwaddnstr(WINDOW *win, int y, int x, const char *str, int n);

int printw(char *fmt, ...);

int wprintw(WINDOW *win, char *fmt, ...);

int mvprintw(int y, int x, char *fmt, ...);

int mvwprintw(WINDOW *win, int y, int x, char *fmt, ...);

int vwprintw(WINDOW *win, char *fmt, va_list);