#include <game.h>
#include <ncurses.h>

int main () {
    int x,y;
    initscr ();
    start_color ();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_BLACK,COLOR_GREEN);
    init_pair(5,COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(6,COLOR_WHITE,COLOR_MAGENTA);
    init_pair(7,COLOR_GREEN,COLOR_BLACK);
    init_pair(8,COLOR_RED,COLOR_BLACK);
    noecho ();
    curs_set (0);
    getmaxyx (stdscr,y,x);
    mvprintw (0,0,"%s", "figlet JOGO");
    char s = 'o';
    while (s != 'e') {
        erase ();
        FILE *f;
        f = fopen ("ASCIIart/Game.txt","r+");
        char n[5][29];
        for (int i = 0;i < 5;i++) {
            for (int j = 0;j < 29;j++) {
                char c = (char) fgetc (f);
                n[i][j] = c;
            }
        }
        fclose (f);
        for (int i = 0;i < 5;i++) {
            for (int j = 0;j < 29;j++) {
                mvprintw (2+i,(x/2)-18+j,"%c",n[i][j]);
            }
        }
        mvprintw ((y/2)-2,(x/2)-9,"%s","Play (p)");
        mvprintw ((y/2),(x/2)-11,"%s","Settings (s)");
        mvprintw ((y/2)+2,(x/2)-9,"%s","Exit (e)");
        refresh ();
        s = (char) getchar ();
        if (s == 'p') {
            game ();
        }
        else {
            if (s == 's') {
                erase ();
                mvprintw (y/2,x/2,"%s","There's no settings it's a terminal roguelike");
                refresh ();
                getchar ();
            }
        }
    }
    endwin();
    return 0;
}
