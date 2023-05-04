#ifndef GAME_H
#define GAME_H

#include "play.c"
//#include "map.c"
#include <ncurses.h>

// Map* mapa;

void game () {
    int y,x,floor,c;
    floor = 0;
    initscr ();
    start_color ();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    noecho ();
    curs_set(0);
    getmaxyx (stdscr,y,x);
    x-=(x/10);
    while (floor < 5) {
        erase ();
        mapa = createmap (x,y);
        for (int i = 0;i < y;i++) {
            for (int j = 0;j < x;j++) {
                if (mapa[i][j].ch == '#'){
                    attrset (COLOR_PAIR(1));
                    mvprintw(i,j,"%c",mapa[i][j].ch);
                }
                else {
                    attrset (COLOR_PAIR(2));
                    mvprintw(i,j,"%c",mapa[i][j].ch); 
                }
            }
        }
        refresh ();
        c = play (mapa,x,y);
        if (c != 2) break;
        else floor++;
    }
    endwin ();
}

#endif