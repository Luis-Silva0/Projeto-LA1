#include "map.c"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "play.h"
#include "map.h"

int movement(Game game) {
    int tx,ty,t,walk_mob;
    t = 0;
    char s = '1';
    while (s != 'q') {
        if (t != time(0)) {
            for (int i = 0; i < 57; i++) {
                mvprintw (0, i, "%s", " ");
            }
        }
        walk_mob = rand()%3;
        t = time(0);
        s = (char) getchar();
        tx = game->player->p.x;
        ty = game->player->p.y;
        erase();
        switch (s)
        {
        case 'w':
            game->player->p.y--;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                if (game->map[game->player->p.y][game->player->p.x].ch == '#') {
                    game->player->p.y++;
                    attrset(COLOR_PAIR(2));
                    mvprintw(0,0,"%s","Wall here"); 
                }
                else {
                    game->player->p.y++;
                    /*Quando fizermos a mob list pomos aqui o dano ao mob*/
                }
                
            }
            else {
                mvprintw(game->player->p.y, game->player->p.x, "%c", game->player->character);
                mvprintw(ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 's':
            game->player->p.y++;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                game->player->p.y--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player->p.y,game->player->p.x,"%c",game->player->character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 'a':
            game->player->p.x--;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                game->player->p.x++;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player->p.y,game->player->p.x,"%c",game->player->character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 'd':
            game->player->p.x++;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                game->player->p.x--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player->p.y,game->player->p.x,"%c",game->player->character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                }
            break;
        case 'k':
            game->player->health = 0;
            break;
        case 'i':
            game->godMode = !game->godMode;
            mvprintw (0,0,"%s","Baby Mode Activated");
            break;
        default:
            break;
        }
        mob_movement(game->player->p, game->map, walk_mob);
        printMap(game);
        mvprintw (4,((game->maxX*10)/9) - 12,"%s %d","Health:",game->player->health);
        radar (((game->maxX*10)/9) - 12, game->player->p);
        refresh ();
        if (game->map[game->player->p.y][game->player->p.x].ch == 's') {
            attrset(COLOR_PAIR(2));
            mvprintw (0,0,"%s","Once you go down you can't go back up are you sure: Y / N");
            refresh();
            s = (char) getchar ();
            switch (s)
            {
            case 'y':
                return 1;
            case 'n':
                break;
            default:
                break;
            }
        }
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                if (game->map[(game->player->p.y)+i][(game->player->p.x)+j].ch == 'G') {
                    int d = rand () % 15;
                    if (d < 4) {
                        d = 0;
                    }
                    d = d - ((int) game->player->classe.defense*0.75);
                    if (d >= 0) {
                        game->player->health -= d;
                    }                    
                    break;
                }
            }
            if(game->player->health <= 0){
                break;
            }
        }
        if (game->player->health <= 0) {
            return 0;
        }
    }    
    return 2;
}

int play (Map *mapa, int maxX, int maxY,Player *player) {
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
        else {
            (*player).p.x = myx;
            (*player).p.y = myy;
        }
    }
    
    Game game = (Game) malloc(sizeof(struct game));
    game->map = mapa;
    game->maxX = maxX;
    game->maxY = maxY;
    game->player = player;
    game->godMode = false;

    printMap(game);
    refresh ();

    int r = movement(game);

    return r;
}
