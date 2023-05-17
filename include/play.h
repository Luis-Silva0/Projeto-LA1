#ifndef PLAY_H
#define PLAY_H

#include "map.h"

typedef struct pos {
    int y;
    int x;
} Position;

typedef struct classe {
    int attack;
    int defense;
    int range;
    int atkspd;
} Class;

typedef struct player {
    Position p;
    char character;
    int health,money;
    Class classe;
} Player;

#endif //PLAY_H
