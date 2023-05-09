#ifndef PLAY_H
#define PLAY_H

#include "map.h"

typedef struct pos {
    int y;
    int x;
} Position;

typedef struct class {
    int attack;
    int range;
    int atkspd;
} Class;

typedef struct player {
    Position p;
    char character;
    int health;
    Class classe;
} Player;

#endif //PLAY_H
