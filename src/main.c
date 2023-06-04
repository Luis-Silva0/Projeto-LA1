#include <game.h>
#include <ncurses.h>

int main () {
    int x,y;
    initscr ();
    start_color ();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,24);
    init_pair(5,23,23);
    init_pair(6,COLOR_WHITE,23);
    init_pair(7,COLOR_GREEN,COLOR_BLACK);
    init_pair(8,COLOR_RED,COLOR_BLACK);
    init_pair(12,24,24);
    init_color(20,trans(51)-201, trans(184)-201, trans(100)-201);
    init_color(21,trans(144)-201, trans(238)-201, trans(144)-201);
    init_color(22,trans(4), trans(55), trans(242));
    init_color(23,trans(112), trans(128), trans(144));
    init_color(24,trans(5), trans(3), trans(1));
    init_pair(9,21,21);
    init_pair(10,20,20);
    init_pair(11,22,22);
    init_pair(13,COLOR_BLACK,COLOR_WHITE);
    init_pair(14,COLOR_YELLOW,COLOR_YELLOW);
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
                mvprintw (y/2,x/2-20,"%s","There's no settings it's a terminal roguelike");
                refresh ();
                getchar ();
            }
        }
    }
    endwin();
    return 0;
}
