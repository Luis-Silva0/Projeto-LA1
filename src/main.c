#include <game.h>
#include <ncurses.h>

int main () {
    int x,y;
    initscr ();
    start_color ();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_BLACK,COLOR_GREEN);
    noecho ();
    curs_set (0);
    getmaxyx (stdscr,y,x);
    mvprintw (0,0,"%s", "figlet JOGO");
    char s = 'o';
    while (s != 'e') {
        erase ();
        mvprintw ((y/2)-2,(x/2)-9,"%s","Play (p)");
        mvprintw ((y/2)+2,(x/2)-9,"%s","Exit (e)");
        refresh ();
        s = (char) getchar ();
        if (s == 'p') {
            game ();
        }
    }
    endwin();
    return 0;
}
