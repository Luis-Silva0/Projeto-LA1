#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "map.c"

Map* createshop (int x, int y){
    Map* mapa = calloc (y+1,sizeof(Map));
    for (int i = 0;i <= y;i++) {
        mapa[i] = calloc (x+1,sizeof(char)+sizeof(bool));
    }
    for (int i = 0;i <= y;i++) {
        for (int j = 0;j <= x;j++) {
            mapa[i][j].ch = ':';
            mapa[i][j].walkable = false;
        }
    }
    srand(clock ());
    int salas = 2, acc = 0;
    rooms = calloc (salas,4*sizeof(int));
    while (acc < salas){
        int bx, by, lx, ly;
        if (acc == 0){
            bx = 20;
            by = 8;
            lx = x - 44;
            ly = y - 20;
        }
        else{
            bx = x/2 - 12;
            by = y - 11;
            lx = 24;
            ly = 7;
        }
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
                mapa[j][k].ch = '.';
                mapa[j][k].walkable = true;
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
            mapa[center2.y][center2.x].ch = 's';
            mapa[center2.y][center2.x].walkable = true;
        }
    }
    FILE *f;
    f = fopen("ASCIIart/Shop.txt","r");
    for (int i = 1;i < 7;i++) {
        for (int j = x/2-15;j < x/2+15;j++) {
            char c = fgetc (f);
            mapa[i][j].ch = c;
            mapa[i][j].walkable = false;
        }
        mapa[i][(x/2+14)].ch = ' ';
    }
    fclose (f);
    return mapa;
}