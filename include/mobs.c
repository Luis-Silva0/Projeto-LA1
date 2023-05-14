#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "map.h"

typedef struct mobs
{
    Position pos_m;
    char mob_char;
    int mob_health;
} Mob;

void create_mob (int pos_y, int pos_x, Map *m){
    if (m[pos_y][pos_x].ch == '.' || m[pos_y][pos_x].ch == '+'){
        m[pos_y][pos_x].ch = 'G';
        m[pos_y][pos_x].walkable = false;
    }
}
