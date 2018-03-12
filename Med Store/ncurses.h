#include <stdarg.h>

#include <varargs.h>

extern WINDOW *stdscr;

extern WINDOW *curscr;

#define COLS	0

#define LINES	0

#define bool int

#define TRUE 1

#define FALSE 0

#define KEY_UP 0

#define KEY_DOWN 1

#define KEY_BACKSPACE 2

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

int keypad(WINDOW *win, bool bf);

void getyx(WINDOW *win, int y, int x);

int addch(const char ch);

int border(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);

int wborder(WINDOW *win, char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);

int box(WINDOW *win, char verch, char horch);

int hline(char ch, int n);

int whline(WINDOW *win, char ch, int n);

int vline(char ch, int n);

int wvline(WINDOW *win, char ch, int n);

mvhline(int y, int x, char ch, int n);

mvwhline(WINDOW *, int y, int x, char ch, int n);

int mvvline(int y, int x, char ch, int n);

int mvwvline(WINDOW *, int y, int x, char ch, int n);

int cbreak(void);

int nocbreak(void);

int echo(void);

int noecho(void);

int halfdelay(int tenths);

int intrflush(WINDOW *win, bool bf);

int keypad(WINDOW *win, bool bf);

int meta(WINDOW *win, bool bf);

int nodelay(WINDOW *win, bool bf);

int raw(void);

int noraw(void);

void noqiflush(void);

void qiflush(void);

int notimeout(WINDOW *win, bool bf);

void timeout(int delay);

void wtimeout(WINDOW *win, int delay);

int typeahead(int fd);

WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);

int delwin(WINDOW *win);

int mvwin(WINDOW *win, int y, int x);

WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);

WINDOW *derwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);

int mvderwin(WINDOW *win, int par_y, int par_x);

WINDOW *dupwin(WINDOW *win);

void wsyncup(WINDOW *win);

int syncok(WINDOW *win, bool bf);

void wcursyncup(WINDOW *win);

void wsyncdown(WINDOW *win);

int refresh(void);

int wrefresh(WINDOW *win);

int wnoutrefresh(WINDOW *win);

int doupdate(void);

int redrawwin(WINDOW *win);

int wredrawln(WINDOW *win, int beg_line, int num_lines);

int erase(void);

int werase(WINDOW *win);

int clear(void);

int wclear(WINDOW *win);

int clrtobot(void);

int wclrtobot(WINDOW *win);

int clrtoeol(void);

int wclrtoeol(WINDOW *win);

int touchwin(WINDOW *win);

int touchline(WINDOW *win, int start, int count);

int untouchwin(WINDOW *win);

int wtouchln(WINDOW *win, int y, int n, int changed);

int is_linetouched(WINDOW *win, int line);

int is_wintouched(WINDOW *win);