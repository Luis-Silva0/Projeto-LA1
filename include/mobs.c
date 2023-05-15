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
        l_goblin = malloc(sizeof(struct Lista_mobs) * 30);
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
    if (m[pos_y][pos_x].ch == '.' || m[pos_y][pos_x].ch == '+'){
        Mob goblin;
        goblin = malloc(sizeof(struct mobs));

        goblin->pos_m.y = pos_y;
        goblin->pos_m.x = pos_x;
        goblin->mob_char = 'G';
        goblin->mob_health = 20;

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

int mob_move_space(int pos_p, int pos_m){
    if (pos_p < pos_m){
        return pos_m - 1;
    }
    if (pos_p > pos_m){
        return pos_m + 1;
    }
    return pos_m;
}

void mob_movement (Position pos_p, Map *m, int walk){
    while (l_goblin->prox != NULL && walk == 0){
        int difx, dify;
        difx = abs(pos_p.x - l_goblin->atual->pos_m.x);
        dify = abs(pos_p.y - l_goblin->atual->pos_m.y);
        if (difx <= 4 && dify <= 4){
            int new_x = mob_move_space(pos_p.x, l_goblin->atual->pos_m.x);
            int new_y = mob_move_space(pos_p.y, l_goblin->atual->pos_m.y);
            if (difx > dify && (m[l_goblin->atual->pos_m.y][new_x].walkable) == true && new_x != pos_p.x){
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = '.';
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                l_goblin->atual->pos_m.x = new_x;
                m[l_goblin->atual->pos_m.y][new_x].ch = 'G';
                m[l_goblin->atual->pos_m.y][new_x].walkable = false;
            }
            else if((m[new_y][l_goblin->atual->pos_m.x].walkable) == true && new_y != pos_p.y){
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = '.';
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                l_goblin->atual->pos_m.y = new_y;
                m[new_y][l_goblin->atual->pos_m.x].ch = 'G';
                m[new_y][l_goblin->atual->pos_m.x].walkable = false;
            }
        }
        l_goblin = l_goblin->prox;
    }
    while (l_goblin->ant != NULL){
        l_goblin = l_goblin->ant;
    }
    // se os mobs estiverem a 3 blocos de raio do player, movem-se para ele;
    // escolher o caminho mais curto;
    // verificar se a superficie é walkable;
}
