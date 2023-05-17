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
    char floor;
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
        l_goblin = malloc(sizeof(struct Lista_mobs) * 50);
        l_goblin->atual = goblin;
        l_goblin->ant = NULL;
        l_goblin->prox = NULL;
        l_goblin->Max = 1;
    }
    else{
        int check = 0;
        while (l_goblin->prox != NULL){
            if (l_goblin->atual->pos_m.x == goblin->pos_m.x && l_goblin->atual->pos_m.y == goblin->pos_m.y){
                check = 1;
            }
            l_goblin = l_goblin->prox;
        }
        if (check == 0){
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
}

void create_mob (int pos_y, int pos_x, Map *m, int fog){
    
    Mob goblin;
    goblin = malloc(sizeof(struct mobs));
    goblin->pos_m.y = pos_y;
    goblin->pos_m.x = pos_x;
    goblin->mob_char = 'G';
    goblin->mob_health = 20;
    goblin->floor = m[pos_y][pos_x].ch;
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

void radar (int x, Position pos){
    int y = 6;
    while (l_goblin->prox != NULL){
        mvprintw(y,x,"G = %d %d", (l_goblin->atual->pos_m.x), (l_goblin->atual->pos_m.y));
        y++;
        l_goblin = l_goblin->prox;
    }
    while (l_goblin->ant != NULL){
        l_goblin = l_goblin->ant;
    }
    mvprintw(5,x,"@ = %d %d ", (pos.x), (pos.y));
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
    srand(clock());
    while (l_goblin->prox != NULL && walk != 0){
        int difx, dify;
        difx = abs(pos_p.x - l_goblin->atual->pos_m.x);
        dify = abs(pos_p.y - l_goblin->atual->pos_m.y);
        if (difx <= 4 && dify <= 4){
            int new_x = mob_move_space(pos_p.x, l_goblin->atual->pos_m.x);
            int new_y = mob_move_space(pos_p.y, l_goblin->atual->pos_m.y);
            if (difx > dify && (m[l_goblin->atual->pos_m.y][new_x].walkable) == true && new_x != pos_p.x){
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = l_goblin->atual->floor;
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                l_goblin->atual->floor = m[l_goblin->atual->pos_m.y][new_x].ch;
                l_goblin->atual->pos_m.x = new_x;
                m[l_goblin->atual->pos_m.y][new_x].ch = 'G';
                m[l_goblin->atual->pos_m.y][new_x].walkable = false;
            }
            else if((m[new_y][l_goblin->atual->pos_m.x].walkable) == true && new_y != pos_p.y){
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = l_goblin->atual->floor;
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                l_goblin->atual->floor = m[new_y][l_goblin->atual->pos_m.x].ch;
                l_goblin->atual->pos_m.y = new_y;
                m[new_y][l_goblin->atual->pos_m.x].ch = 'G';
                m[new_y][l_goblin->atual->pos_m.x].walkable = false;
            }
        }
/*        else {
            int d = rand ()%4;
            if (d == 0 && m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x+1].walkable == true) {
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = l_goblin->atual->floor;
                if (m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '.' || m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '+') {
                    m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                }
                else m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                l_goblin->atual->floor = m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x+1].ch;
                l_goblin->atual->pos_m.x = l_goblin->atual->pos_m.x+1;
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = 'G';
                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
            }
            else {
                if (d == 1 && m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x-1].walkable == true) {
                    m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = l_goblin->atual->floor;
                    if (m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '.' || m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '+') {
                        m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                    }
                    else m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                    l_goblin->atual->floor = m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x-1].ch;
                    l_goblin->atual->pos_m.x = l_goblin->atual->pos_m.x-1;
                    m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = 'G';
                    m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                }
                else {
                    if (d == 2 && m[l_goblin->atual->pos_m.y+1][l_goblin->atual->pos_m.x].walkable == true) {
                        m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = l_goblin->atual->floor;
                        if (m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '.' || m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '+') {
                            m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                        }
                        else m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                        l_goblin->atual->floor = m[l_goblin->atual->pos_m.y+1][l_goblin->atual->pos_m.x+1].ch;
                        l_goblin->atual->pos_m.y = l_goblin->atual->pos_m.y+1;
                        m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = 'G';
                        m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                    }
                    else {
                        if (m[l_goblin->atual->pos_m.y-1][l_goblin->atual->pos_m.x].walkable == true) {
                            m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = l_goblin->atual->floor;
                            if (m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '.' || m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch == '+') {
                                m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = true;
                            }
                            else m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                            l_goblin->atual->floor = m[l_goblin->atual->pos_m.y-1][l_goblin->atual->pos_m.x].ch;
                            l_goblin->atual->pos_m.y = l_goblin->atual->pos_m.y-1;
                            m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].ch = 'G';
                            m[l_goblin->atual->pos_m.y][l_goblin->atual->pos_m.x].walkable = false;
                        }
                    }
                }
            }
        }*/
        l_goblin = l_goblin->prox;
    }
    while (l_goblin->ant != NULL){
        l_goblin = l_goblin->ant;
    }
    // se os mobs estiverem a 4 blocos de raio do player, movem-se para ele;
    // escolher o caminho mais curto;
    // verificar se a superficie é walkable;
}
