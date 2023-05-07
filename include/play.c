#include "map.c"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "play.h"
#include "map.h"

int movement(Game game) {
    int tx,ty,t;
    t = 0;
    char s = '1';
    while (s != 'q') {
        if (t != time(0)) {
            for (int i = 0; i < 57; i++) {
                mvprintw (0, i, "%s", " ");
            }
        }
        t = time(0);
        s = (char) getchar();
        tx = game->player.p.x;
        ty = game->player.p.y;
        erase();
        switch (s)
        {
        case 'w':
            game->player.p.y--;
            if (game->map[game->player.p.y][game->player.p.x].walkable == false) {
                game->player.p.y++;
                attrset(COLOR_PAIR(2));
                mvprintw(0,0,"%s","Wall here");
            }
            else {
                mvprintw(game->player.p.y, game->player.p.x, "%c", game->player.character);
                mvprintw(ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 's':
            game->player.p.y++;
            if (game->map[game->player.p.y][game->player.p.x].walkable == false) {
                game->player.p.y--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player.p.y,game->player.p.x,"%c",game->player.character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 'a':
            game->player.p.x--;
            if (game->map[game->player.p.y][game->player.p.x].walkable == false) {
                game->player.p.x++;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player.p.y,game->player.p.x,"%c",game->player.character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 'd':
            game->player.p.x++;
            if (game->map[game->player.p.y][game->player.p.x].walkable == false) {
                game->player.p.x--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player.p.y,game->player.p.x,"%c",game->player.character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 'k':
            game->player.health = 0;
            break;     
        default:
            break;
        }
        printMap(game);
        refresh ();
        if (game->map[game->player.p.y][game->player.p.x].ch == 's') {
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
        if (game->player.health == 0) {
            return 0;
        }
    }    
    return 1;
}

int play (Map *mapa, int maxX, int maxY) {
    srand(clock());

    int myx, myy;
    myx = myy = -1;
    while (myx == -1 || myy == -1){
        myy = (rand () % maxY);
        myx = (rand () % maxX);
        if (mapa[myy][myx].walkable == false) {
            myx = -1;
            myy = -1;
        }
    }

    Player player = {{myy,myx},'@',100};
    Game game = (Game) malloc(sizeof(struct game));
    game->map = mapa;
    game->maxX = maxX;
    game->maxY = maxY;
    game->player = player;

    printMap(game);
    refresh ();

    int r = movement(game);

    return r;
}
