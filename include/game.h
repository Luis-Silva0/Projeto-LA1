#ifndef GAME_H
#define GAME_H

#include "play.c"
//#include "map.c"
#include <ncurses.h>
#include <string.h>

// Map* mapa;
Player characterselect () {
    FILE *f;
    Player r;
    erase ();
    int y,x;
    getmaxyx (stdscr,y,x);
    mvprintw (1,(x/2)-13,"%s","Choose starting character:");
    mvprintw ((y/4)-5,(x/2)-13,"%s","Swordsman (s)");
    mvprintw ((2*y/4)-5,(x/2)-13,"%s","Archer (a)");
    mvprintw ((3*y/4)-5,(x/2)-13,"%s","Gunner (g)");
    mvprintw ((4*y/4)-5,(x/2)-13,"%s","Viking (v)");
    refresh ();
    char c = (char) getchar ();
    switch (c)
    {
    case 's':
        erase ();
        mvprintw (1,1,"%s","Swordsman");
        f = fopen ("/home/biokiller/Desktop/Universidade/LA1/Projeto/jogo/ASCIIart/sword.txt","r"); 
        char s[30][19];
        for (int i = 0;i < 30;i++) {
            for (int j = 0;j < 19;j++) {
                char c = (char) fgetc (f);
                s[i][j] = c;
            }
        }
        fclose (f);
        for (int i = 0;i < 30;i++) {
            for (int j = 0;j < 19;j++) {
                mvprintw (y-36+i,x-40+j,"%c",s[i][j]);
            }
        }
        
        r.p.x = -1;
        r.p.y = -1;
        r.character = '@';
        r.health = 100;
        r.classe.attack = 10;
        r.classe.range = 2;
        r.classe.range = 1; 
        
        break;
    
    default:
        r.p.x = -1;
        r.p.y = -1;
        r.character = '@';
        r.health = 100;
        r.classe.attack = 10;
        r.classe.range = 2;
        r.classe.range = 1;
        break;
    }
    refresh ();
    getchar ();
    return r;
}

void game () {
    Player player = characterselect ();
    int y,x,tx,floor,c;
    floor = 0;
    curs_set(0);
    getmaxyx (stdscr,y,x);
    tx = x;
    x-=(x/10);
    while (floor < 6) {
        erase ();
        mapa = createmap (x,y);
        c = play (mapa,x,y,player);
        if (c == 1) {
            floor++;
        }
        else {
            if (c == 0) {
            erase ();
            mvprintw (y/2,(tx/2)-9,"%s","You Died");
            mvprintw ((y/2)+1,(tx/2)-16,"%s","Press any key to leave");
            refresh();
            }
            else {
            erase ();
            mvprintw (y/2,(tx/2)-4,"%s","You ragequitted?");
            mvprintw ((y/2)+1,(tx/2)-18,"%s","Press any key to be stupid somewhere else...");
            refresh();
            }
            break;
        }
    }
    getchar ();
}



#endif
