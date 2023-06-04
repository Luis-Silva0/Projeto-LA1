#ifndef STORE_H
#define STORE_H

typedef struct item_s{
    char item[40];
    int enchantment;
    int value;
    int price;
} *Item_s;

typedef struct litems_s {
    Item_s it_w;
    Item_s it_a;
    int potions;
} *LItems_s;

#endif