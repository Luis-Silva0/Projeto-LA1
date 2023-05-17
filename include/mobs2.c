#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "map.h"

typedef struct mob2 {
    char mob_char;
    int pos_x,pos_y;
    int dano,vida,range;
} Mob2;
typedef struct mob_list {
    Mob2 m;
    struct mob_list *prox;
} *Mob_list;

void show_mobs (Mob_list l,int x,Game game){
    int y = 8;
    while (l) {
        if (l->m.vida > 0) {
            mvprintw (y,x,"%c: %d %d %d",l->m.mob_char,l->m.pos_x,l->m.pos_y,l->m.vida);
            refresh();
            init_pair(4,COLOR_RED,COLOR_YELLOW);
            int tempx,tempy;
            tempx = l->m.pos_x;
            tempy = l->m.pos_y;
            if ((tempx <= game->player->p.x + 7 && tempx >= game->player->p.x - 7) && (tempy <= game->player->p.y + 7 && tempy >= game->player->p.y - 7) && !game->godMode) {
                attron (COLOR_PAIR(4));
                mvprintw (tempy,tempx,"%c",l->m.mob_char);
                attroff (COLOR_PAIR(4));
                refresh();
            }
            else if (game->godMode) {
                attron (COLOR_PAIR(4));
                mvprintw (tempy,tempx,"%c",l->m.mob_char);
                attroff (COLOR_PAIR(4));
                refresh();
            }
            y++;
        }
        l = l->prox;
    }
}

void move_mobs (Game game,Mob_list *l,int d) {
    Mob_list *head;
    int r,c;
    srand(clock());
    head = &(*l);
    while (*l) {
        c = 0;
        int mx = (*l)->m.pos_x;
        int my = (*l)->m.pos_y;
        while (c == 0) {
            int difx = game->player->p.x - (*l)->m.pos_x,dify = game->player->p.y - (*l)->m.pos_y;
            if (abs(difx) < 4 && abs(dify) < 4 && d != 0) {
                if (abs(dify) < abs(difx)) {
                    if (difx < 0) {
                        if (game->map[my][mx-1].walkable == true && mx-1 != game->player->p.x) {
                            (*l)->m.pos_x--;
                        }
                        c++;
                    }
                    else {
                        if (game->map[my][mx+1].walkable == true && mx+1 != game->player->p.x) {
                            (*l)->m.pos_x++;
                        }
                        c++;
                    }
                }
                else {
                    if (dify < 0) {
                        if (game->map[my-1][mx].walkable == true && my-1 != game->player->p.y) {
                            (*l)->m.pos_y--;
                        }
                        c++;
                    }
                    else {
                        if (game->map[my+1][mx].walkable == true && my+1 != game->player->p.y) {
                            (*l)->m.pos_y++;
                        }
                        c++;
                    }
                }
            }
            else {
                r = rand()%4;
                if (r%2 == 1) {
                    if (r == 1) {
                        if (game->map[my][mx-1].walkable == true) {
                            (*l)->m.pos_x--;
                            c++;
                        }
                    }
                    else {
                        if (game->map[my][mx+1].walkable == true) {
                            (*l)->m.pos_x++;
                            c++;
                        }
                    };
                }
                else {
                    if (r == 0) {
                        if (game->map[my-1][mx].walkable == true) {
                            (*l)->m.pos_y--;
                            c++;
                        }
                    }
                    else {
                        if (game->map[my+1][mx].walkable == true) {
                            (*l)->m.pos_y++;
                            c++;
                        }
                    }
                }
            }
        }
        l = &((*l)->prox);
    }
    l = head;
}

void dropitem (Player *p){
    srand(clock());
    int drop = rand()%4;
    if (drop == 0){
        (*p).bag.potion ++;
        mvprintw(1,0,"You got a potion!");
    }
}

void combat (Mob_list *l,Player *p) {
    Mob_list *head;
    head = &(*l);
    int mob_money;
    srand (clock());
    while (*l) {
        if ((*l)->m.vida > 0) {
            if ((*l)->m.range >= abs((*l)->m.pos_x - (*p).p.x) && (*l)->m.range >= abs((*l)->m.pos_y - (*p).p.y)) {
                if ((*l)->m.dano - (*p).classe.defense >= 0) {
                    (*p).health -= ((*l)->m.dano - (*p).classe.defense);            }
            }
            if ((*p).classe.range >= abs((*l)->m.pos_x - (*p).p.x) && (*p).classe.range >= abs((*l)->m.pos_y - (*p).p.y)) {
                (*l)->m.vida -= (*p).classe.attack;
                if ((*l)->m.vida <= 0){
                    mob_money = rand()%10 + 5;
                    (*p).money += mob_money;
                    mvprintw(0,0,"You picked up %d gold", mob_money);
                    dropitem(&(*p));
                } 
            }
        }
        l = &((*l)->prox);
    }
    l = head;
}

Mob_list create_mob2 (Map *m,int x,int y,int n,int floor) {
    Mob_list ml = malloc (sizeof(struct mob_list));
    Mob_list *temp = &ml;
    int i = 0;
    srand (clock());
    int tempy,tempx;
    while (i < n) {
        (*temp)->prox = malloc (sizeof(struct mob_list));
        tempy = tempx = -1;
        while (tempy == -1 || tempx == -1) {
            tempy = rand()%y;
            tempx = rand()%x;
            if (m[tempy][tempx].walkable == false) {
                tempy = -1;
                tempx = -1;
            }
        }
        (*temp)->m.pos_x = tempx;
        (*temp)->m.pos_y = tempy;
        int p = rand()%20;
        if (p < 9) {
            (*temp)->m.mob_char = 'D';
            (*temp)->m.dano = rand()%6 + 5 + (floor * 3);
            (*temp)->m.vida = 20;
            (*temp)->m.range = 3;
        }
        else {
            if (p >= 9 && p < 19-floor) {
                (*temp)->m.mob_char = 'T';
                (*temp)->m.dano = rand()%5 + 8 + (floor * 3);
                (*temp)->m.vida = 10;
                (*temp)->m.range = 2;
            }
            else if(p >= (19-floor)){
                (*temp)->m.mob_char = 'H';
                (*temp)->m.dano = rand()%11 + 15 + (floor * 3);
                (*temp)->m.vida = 50;
                (*temp)->m.range = 3;
            }
        }
    temp = &((*temp)->prox);
    i++;
    }
    *temp = NULL;
    return ml;
}