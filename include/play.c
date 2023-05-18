#include "map.c"
#include "inventory.c"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "play.h"
#include "map.h"
#include "mobs2.c"

int movement(Game game,int floor) {
    int tx,ty,t;
    int walk_mob;
    t = 0;
    char s = '1';
    Mob_list mobs;
    mobs = create_mob2(game->map,(game->maxX*10)/9 - 25,game->maxY,8,floor);
    while (s != 'q') {
        show_mobs(mobs,((game->maxX*10)/9) - 18,game);     
        if (t != time(0)) {
            for (int i = 0; i < 57; i++) {
                mvprintw (0, i, "%s", " ");
            }
        }
        walk_mob = rand()%4;
        t = time(0);
        s = (char) getchar();
        tx = game->player->p.x;
        ty = game->player->p.y;
        erase();
        switch (s)
        {
        case 'w' :
        case '8' :
            game->player->p.y--;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                if (game->map[game->player->p.y][game->player->p.x].ch == '#') {
                    game->player->p.y++;
                    attrset(COLOR_PAIR(2));
                    mvprintw(0,0,"%s","Wall here"); 
                }                
            }
            else {
                mvprintw(game->player->p.y, game->player->p.x, "%c", game->player->character);
                mvprintw(ty,tx,"%c",game->map[ty][tx].ch);
                move_mobs(game,&mobs,walk_mob);
                combat(&mobs,game);
                }
            break;
        case 's':
        case '2':
            game->player->p.y++;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                game->player->p.y--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player->p.y,game->player->p.x,"%c",game->player->character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                move_mobs(game,&mobs,walk_mob);
                combat(&mobs,game);
                }
            break;
        case 'a':
        case '4':
            game->player->p.x--;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                game->player->p.x++;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player->p.y,game->player->p.x,"%c",game->player->character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                move_mobs(game,&mobs,walk_mob);
                }
            break;
        case 'd':
        case '6':
            game->player->p.x++;
            if (game->map[game->player->p.y][game->player->p.x].walkable == false) {
                game->player->p.x--;
                attrset(COLOR_PAIR(2));
                mvprintw (0,0,"%s","Wall here");
            }
            else {
                mvprintw (game->player->p.y,game->player->p.x,"%c",game->player->character);
                mvprintw (ty,tx,"%c",game->map[ty][tx].ch);
                move_mobs(game,&mobs,walk_mob);
                combat(&mobs,game);
                }
            break;
        case 'k':
            game->player->health = 0;
            break;
        case 'g':
            game->godMode = !game->godMode;
            break;
        case 'i' :
            check_inv(game->player);
            s = getchar();
            break;
        case 'p' :
            game->player->bag.potion --;
            game->player->health += 25;
            if (game->player->health > 100){
                game->player->health = 100;
            }
            break;
        default:
            break;
        }
        actionShow (game);
//        mob_movement(game->player->p, game->map, walk_mob);
        printMap(game);
        if (game->godMode) {
            attron (COLOR_PAIR(6));
            mvprintw (0,0,"%s","Baby Mode Activated");
            attroff (COLOR_PAIR(6));
        }
        mvprintw (2,((game->maxX*10)/9) - 17,"%s %d","Health:",game->player->health);
        mvprintw (3,((game->maxX*10)/9) - 17,"%s %d","Money:",game->player->money);
        //radar (((game->maxX*10)/9) - 12, game->player->p);
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
        if (game->player->health <= 0) {
            return 0;
        }
    }    
    return 2;
}

int play (Map *mapa, int maxX, int maxY,Player *player,int floor) {
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

    mvprintw (2,((game->maxX*10)/9) - 16,"%s %d","Health:",game->player->health);
    mvprintw (3,((game->maxX*10)/9) - 16,"%s %d","Money:",game->player->money);

    printMap(game);
    refresh ();

    int r = movement(game,floor);

    return r;
}
