#ifndef PLAY_H
#define PLAY_H

#include "map.h"

typedef struct pos {
    int y;
    int x;
} Position;

typedef struct classe {
    char * name;
    int attack;
    int defense;
    int range;
} Class;

typedef struct item{
    char * item;
    int enchantment;
    int value;
}Item;

typedef struct inventory{
    int potion;
    Item weapon;
    Item armor;
} Inventory;

typedef struct player {
    Position p;
    char character;
    int health,money;
    Class classe;
    Inventory bag;
} Player;

#endif //PLAY_H
