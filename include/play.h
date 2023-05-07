#ifndef PLAY_H
#define PLAY_H

#include "map.h"

typedef struct pos {
    int y;
    int x;
} Position;

typedef struct player {
    Position p;
    char character;
    int health;
} Player;

#endif //PLAY_H
