//#ifndef MAP_H
//#define MAP_H
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "map.h"
#include "play.h"

bool FOG_OF_WAR_ENABLED = true;

void ligasalas (Position c1,Position c2,Map* m) {
    Position temp;
    temp.x = c1.x;
    temp.y = c1.y;
    while (true) {
        if (abs((temp.x - 1) - c2.x) < abs(temp.x - c2.x)) {
            temp.x--;
        }
        else if (abs((temp.x + 1) - c2.x) < abs(temp.x - c2.x)) {
            temp.x++;
        }
        else if (abs((temp.y - 1) - c2.y) < abs(temp.y - c2.y)) {
            temp.y--;
        }
        else if (abs((temp.y + 1) - c2.y) < abs(temp.y - c2.y)) {
            temp.y++;
        }
        else break;
        m[temp.y][temp.x].ch = '.';
        m[temp.y][temp.x].walkable = true; 
        if (m[temp.y+1][temp.x-1].ch != '.') {
            m[temp.y+1][temp.x-1].ch = '#';
            m[temp.y+1][temp.x-1].walkable = false;
        }
         if (m[temp.y-1][temp.x+1].ch != '.') {
            m[temp.y-1][temp.x+1].ch = '#';
            m[temp.y-1][temp.x+1].walkable = false;
        }
         if (m[temp.y+1][temp.x+1].ch != '.') {
            m[temp.y+1][temp.x+1].ch = '#';
            m[temp.y+1][temp.x+1].walkable = false;
        }
         if (m[temp.y-1][temp.x-1].ch != '.') {
            m[temp.y-1][temp.x-1].ch = '#';
            m[temp.y-1][temp.x-1].walkable = false;
        }
    }
}

Map* createmap (int x, int y) {
    Map* mapa = calloc (y+1,sizeof(Map));
    for (int i = 0;i <= y;i++) {
        mapa[i] = calloc (x+1,sizeof(char)+sizeof(bool));
    }
    srand(clock ());
    int salas = (rand() % 10) + 11;
    int acc = 0;
    rooms = calloc (salas,4*sizeof(int));
    while (salas > acc) {
        int bx,by,lx,ly;
        lx = (rand() % (int)(x*0.15)) + 6;
        ly = (rand() % (int)(y*0.15)) + 6;
        bx = (rand() % (x-1)) + 1;
        by = (rand() % (y-1)) + 1;
        if (bx + lx >= x) bx = bx - lx;
        if (by + ly >= y) by = by - ly;
        rooms[acc].bx = bx;rooms[acc].by = by;rooms[acc].lx = lx;rooms[acc].ly = ly;
        for (int i = by;i < (by+ly);i++) {
            for (int j = bx;j < (bx+lx);j++) {
                mapa[i][j].ch = '#';
                mapa[i][j].walkable = false;
            }
        }
        acc++;
    }
    for (int i = 0;i < salas;i++) {
        for (int j = (1 + rooms[i].by);j < rooms[i].by + rooms[i].ly - 1;j++) {
            for (int k = (1 + rooms[i].bx);k < rooms[i].bx + rooms[i].lx - 1;k++) {
                if (rand()%10 != 1) {
                    mapa[j][k].ch = '.';
                    mapa[j][k].walkable = true;
                }
                else {
                    mapa[j][k].ch = '+';
                    mapa[j][k].walkable = true;
                }
            }
        }
    }
    Position center1,center2;
    for (int i = 0;i < salas-1;i++) {
        center1.x = rooms[i].bx + rooms[i].lx/2;
        center1.y = rooms[i].by + rooms[i].ly/2;
        center2.x = rooms[i+1].bx + rooms[i+1].lx/2;
        center2.y = rooms[i+1].by + rooms[i+1].ly/2;
        ligasalas(center1,center2,mapa);
        if (i == salas-2) {
                    mapa[center1.y][center1.x].ch = 's';
                    mapa[center2.y][center2.x].walkable = true;
                }
    }
    return mapa;
}

void printTile(Game game, int y, int x) {
    if (game->map[y][x].ch == '#') {
        attrset(COLOR_PAIR(1));
        mvprintw(y, x, "%c", game->map[y][x].ch);
    }
    else {
        attrset(COLOR_PAIR(2));
        mvprintw(y, x, "%c", game->map[y][x].ch);
    }
}

void printVisible(Game game, float y, float x) {
    int i;
    float ox,oy;

    oy = (float)game->player.p.y+0.5f;
    ox = (float)game->player.p.x+0.5f;

    for(i = 0; i < 10; i++) {
        int ioy = (int)oy;
        int iox = (int)ox;

        printTile(game, ioy, iox);

        if (game->map[ioy][iox].ch == '#') {
            attrset(COLOR_PAIR(1));

            if (ioy+1 <= game->maxY && game->map[ioy+1][iox].ch == '#') {
                mvprintw(ioy+1, iox, "%c",'#');
            }
            if (ioy-1 >= 0 && game->map[ioy-1][iox].ch == '#') {
                mvprintw(ioy-1, iox, "%c",'#');
            }
            if (iox+1 <= game->maxX && game->map[ioy][iox+1].ch == '#') {
                mvprintw(ioy, iox+1, "%c",'#');
            }
            if (iox-1 >=0 && game->map[ioy][iox-1].ch == '#') {
                mvprintw(ioy, iox-1, "%c",'#');
            }
            return;
        }
        ox+=x;
        oy+=y;
    }
}

void printMap(Game game) {
    float x,y;
    int i;

    if (FOG_OF_WAR_ENABLED) {
        for (i = 0; i < 360; i++) {
            y=sin((float)i*0.01745f);
            x=cos((float)i*0.01745f);
            printVisible(game, y, x);
        }
    } else {
        for (int i = 0; i < game->maxY; i++) {
            for (int j = 0; j < game->maxX; j++) {
                if (game->map[i][j].ch == '#'){
                    attrset(COLOR_PAIR(1));
                    mvprintw(i, j, "%c", game->map[i][j].ch);
                }
                else {
                    attrset(COLOR_PAIR(2));
                    mvprintw(i, j, "%c", game->map[i][j].ch);
                }
            }
        }
    }

    attrset(COLOR_PAIR(2));
    mvprintw(game->player.p.y, game->player.p.x, "%c", game->player.character);
}

//#endif
