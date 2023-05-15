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
} *Mob;

typedef struct Lista_mobs{
    Mob atual;
    struct Lista_mobs *prox;
    struct Lista_mobs *ant;
    int Max;
}* lista_mobs;

lista_mobs l_goblin;

void max_update(int max){
    while (l_goblin->ant != NULL){
        l_goblin = l_goblin->ant;
        l_goblin->Max = max;
    }
}

void mob_list (Mob goblin){
    if (l_goblin == NULL){
        l_goblin = malloc(sizeof(struct Lista_mobs) * 20);
        l_goblin->atual = goblin;
        l_goblin->ant = NULL;
        l_goblin->prox = NULL;
        l_goblin->Max = 1;
    }
    else{
        while (l_goblin->prox != NULL){
            l_goblin = l_goblin->prox;
        }
        lista_mobs temp;
        l_goblin->Max ++;
        int max = l_goblin->Max;
        l_goblin->prox = &(l_goblin [1]);
        temp = l_goblin;
        l_goblin = l_goblin->prox;
        l_goblin->ant = temp;
        l_goblin->atual = goblin;
        l_goblin->prox = NULL;
        l_goblin->Max = max;
        max_update(l_goblin->Max);
    }
}

void create_mob (int pos_y, int pos_x, Map *m, int fog){
    
    Mob goblin;
    goblin = malloc(sizeof(struct mobs));
    
    goblin->pos_m.y = pos_y;
    goblin->pos_m.x = pos_x;
    goblin->mob_char = 'G';
    goblin->mob_health = 20;
    if (m[pos_y][pos_x].ch == '.' || m[pos_y][pos_x].ch == '+'){
        if(fog == 1){
            m[pos_y][pos_x].ch = 'G';
            m[pos_y][pos_x].walkable = false;
        }
        else{
            mvprintw(goblin->pos_m.y,goblin->pos_m.x,"%c",goblin->mob_char);
            m[pos_y][pos_x].ch = 'G';
            m[pos_y][pos_x].walkable = false;
        }
        mob_list(goblin);
    }
}

void mob_movement (Position pos_p){

}
