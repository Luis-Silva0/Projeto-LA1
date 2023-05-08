#include <game.h>
#include <ncurses.h>

int main () {
    int x,y;
    initscr ();
    start_color ();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    noecho ();
    getmaxyx (stdscr,y,x);
    mvprintw (0,0,"%s", "$ figlet JOGO");
    WINDOW* win = newwin(10,30,(y/2)-5,(x/2)-15);
    char s = 'o';
    while (s != 'e') {
        werase (win);
        mvwprintw (win,3,6,"%s","Play (p)");
        mvwprintw (win,7,6,"%s","Exit (e)");
        wrefresh (win);
        s = (char) getchar ();
        if (s == 'p') {
            game ();
        }
    }
    endwin();
    return 0;
}
