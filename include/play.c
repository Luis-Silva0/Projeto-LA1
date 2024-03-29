#include "store.c"
#include "inventory.c"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "play.h"
#include "map.h"

int movement(Game game,int floor,int diff) {
    int tx,ty,t;
    int walk_mob;
    t = 0;
    char s = '1';
    Mob_list mobs;
    LItems list;
    list = NULL;
    mobs = create_mob2(game->map,game->maxX,game->maxY,8,floor, diff);
    while (s != 'q') {
        int p = 0;
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
                combat(&mobs,game,&list,diff);
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
                combat(&mobs,game,&list,diff);
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
                combat(&mobs,game,&list,diff);
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
                combat(&mobs,game,&list,diff);
                }
            break;
        /*case 'k':
            game->player->health = 0;
            break;
        */
        case 'g':
            game->godMode = !game->godMode;
            break;
        case 'i' :
            check_info(game->player);
            s = getchar();
            break;
        case 'p' :
            if (game->player->bag.potion > 0) {
                game->player->bag.potion --;
                game->player->health += 25;
                if (game->player->health > 100){
                    game->player->health = 100;
                }
                actionreload(game,2,0,'n');
                p = 0;
            }
            else p = 1;
            break;
        case 'e':
            check_extrainfo(game);
            s = getchar ();
            break;
        default:
            break;
        }      
//        mob_movement(game->player->p, game->map, walk_mob);
        int ps = 0;
        if (floor % 3 == 2){
            ps = 2;
        }
        printMap(game, ps);
        if (game->godMode) {
            attron (COLOR_PAIR(6));
            mvprintw (0,0,"%s","Baby Mode Activated");
            attroff (COLOR_PAIR(6));
        }
        if (p == 1) {
            actionreload (game,3,0,'n');
        }
        actionShow (game);
        refresh();
        mvprintw (0,((game->maxX*10)/9) - 23,"--------Player--------");
        mvprintw (2,((game->maxX*10)/9) - 18,"%s %d","Health:",game->player->health);
        mvprintw (3,((game->maxX*10)/9) - 18,"%s %d","Gold:",game->player->money);
        checkItem (game,&list);
        if (game->map[game->player->p.y][game->player->p.x].ch == 'b'){
            openShop(game);
        }
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

int play (Map *mapa, int maxX, int maxY,Player *player,int floor, int diff) {
    srand(clock());
    int ps = 0;
    if (floor % 3 == 2){
        ps = 1;
    }
    int myx, myy,mx = (maxX*10)/9 - 25;
    myx = myy = -1;
    while (myx == -1 || myy == -1){
        myy = (rand () % maxY);
        myx = (rand () % mx);
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

    mvprintw (0,((game->maxX*10)/9) - 23,"--------Player--------");
    mvprintw (2,((game->maxX*10)/9) - 18,"%s %d","Health:",game->player->health);
    mvprintw (3,((game->maxX*10)/9) - 18,"%s %d","Gold:",game->player->money);

    printMap(game, ps);
    refresh ();

    int r = movement(game,floor,diff);

    return r;
}
