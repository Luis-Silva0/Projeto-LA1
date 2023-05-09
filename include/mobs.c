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

void create_mob (int pos_y, int pos_x, Map *m, int fog){
    
    Mob goblin;
    
    goblin.pos_m.y = pos_y;
    goblin.pos_m.x = pos_x;
    goblin.mob_char = 'G';
    goblin.mob_health = 20;
    if (m[pos_y][pos_x].ch == '.' || m[pos_y][pos_x].ch == '+'){
        if(fog = 1){
            m[pos_y][pos_x].ch = 'G';
            m[pos_y][pos_x].walkable = false;
        }
        else{
            mvprintw(goblin.pos_m.y,goblin.pos_m.x,"%c",goblin.mob_char);
            m[pos_y][pos_x].ch = 'G';
            m[pos_y][pos_x].walkable = false;
        }
    }
}
