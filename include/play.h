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
} Class;

typedef struct inventory{
    int potion;
    char * weapon;
    int weapon_dmg;
    char * armor;
    int armor_def;
} Inventory;

typedef struct player {
    Position p;
    char character;
    int health,money;
    Class classe;
    Inventory bag;
    // inventory -> 3 slots para já
} Player;

#endif //PLAY_H
