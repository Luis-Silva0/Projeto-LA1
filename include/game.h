#ifndef GAME_H
#define GAME_H

#include "play.c"
//#include "map.c"
#include <ncurses.h>

// Map* mapa;

void game () {
    int y,x,tx,floor,c;
    floor = 0;
    initscr ();
    start_color ();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    noecho ();
    curs_set(0);
    getmaxyx (stdscr,y,x);
    tx = x;
    x-=(x/10);
    while (floor < 5) {
        erase ();
        mapa = createmap (x,y);
        c = play (mapa,x,y);
        if (c == 1) {
            floor++;
        }
        else {
            if (c == 0) {
            erase ();
            mvprintw (y/2,(tx/2)-4,"%s","You Died");
            mvprintw ((y/2)+1,(tx/2)-4,"%s","Press any key to leave");
            refresh();
            }
            break;
        }
    }
    getchar ();
    endwin ();
}

#endif
