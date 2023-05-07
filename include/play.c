#include "map.c"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "play.h"
#include "map.h"

int movement (Player j,Map *m) {
    int tx,ty,t;
    t = 0;
    char s = '1';
    while (s != 'q') {
        if (t != time(0)) {
            for (int i = 0;i < 57;i++) {
                mvprintw (0,i,"%s"," ");
            }
        }
        t = time(0);
        s = (char) getchar ();
        tx = j.p.x;
        ty = j.p.y;
        erase();
        switch (s)
        {
        case 'w':
            j.p.y--;
            if (m[j.p.y][j.p.x].walkable == false) {
                j.p.y++;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (j.p.y,j.p.x,"%c",j.character);
                mvprintw (ty,tx,"%c",m[ty][tx].ch);
                }
            break;
        case 's':
            j.p.y++;
            if (m[j.p.y][j.p.x].walkable == false) {
                j.p.y--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (j.p.y,j.p.x,"%c",j.character);
                mvprintw (ty,tx,"%c",m[ty][tx].ch);
                }
            break;
        case 'a':
            j.p.x--;
            if (m[j.p.y][j.p.x].walkable == false) {
                j.p.x++;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (j.p.y,j.p.x,"%c",j.character);
                mvprintw (ty,tx,"%c",m[ty][tx].ch);
                }
            break;
        case 'd':
            j.p.x++;
            if (m[j.p.y][j.p.x].walkable == false) {
                j.p.x--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (j.p.y,j.p.x,"%c",j.character);
                mvprintw (ty,tx,"%c",m[ty][tx].ch);
                }
            break;
        case 'k':
            j.health = 0;
            break;     
        default:
            break;
        }
        printMap(m, j);
        refresh ();
        if (m[j.p.y][j.p.x].ch == 's') {
            attrset(COLOR_PAIR(2));
            mvprintw (0,0,"%s","Once you go down you can't go back up are you sure: Y / N");
            refresh();
            s = (char) getchar ();
            switch (s)
            {
            case 'y':
                s = 'q';
                return 2;
                break;
            case 'n':
                break;
            default:
                break;
            }
        }
        if (j.health == 0) {
            return 0;
        }
    }    
    return 1;
}

int play (Map * m,int x,int y) {
    srand(clock());
    int myx,myy;
    myx = myy = -1;
    while (myx == -1 || myy == -1){
        myy = (rand () % y);
        myx = (rand () % x);
        if (m[myy][myx].walkable == false) {
            myx = -1;
            myy = -1;
        }
    }
    Player me = {{myy,myx},'@',100};
    printMap(mapa, me);
    refresh ();
    int r = movement(me,m);
    return r;
}
