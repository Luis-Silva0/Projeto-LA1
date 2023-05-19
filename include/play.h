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
    char item[30];
    int enchantment;
    int value;
    int d;
} *Item;

typedef struct litems {
    Item it;
    int x,y;
    struct litems *prox;
} *LItems;

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
