#ifndef MAP_H
#define MAP_H

#include "play.h"

typedef struct action {
    int color;
    char line[30];
} Action;

typedef struct map {
    char ch;
    bool walkable;
} *Map;

typedef struct sala {
    int bx,by,lx,ly;
} *Salas;

typedef struct game {
    Map *map;
    int maxX;
    int maxY;
    bool godMode;
    Action actions[8];
    Player *player;
} *Game;

Salas rooms;
Map* mapa;

#endif //MAP_H
