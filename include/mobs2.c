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
    bool visible;
} Mob2;
typedef struct mob_list {
    Mob2 m;
    struct mob_list *prox;
} *Mob_list;

void show_mobs (Mob_list l,int x,Game game){
    int y = 22;
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
                if (l->m.visible == false) {
                    actionreload (game,4,0,l->m.mob_char);
                    l->m.visible = true; 
                }
                refresh();
            }
            else if (game->godMode) {
                attron (COLOR_PAIR(4));
                mvprintw (tempy,tempx,"%c",l->m.mob_char);
                attroff (COLOR_PAIR(4));
                refresh();
            }
            else l->m.visible = false;
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

void dropitem (Game game, Mob_list l){
    srand(clock());
    int drop_potion = rand()%4;
    int drop_item = rand()%6;
    if (drop_potion == 0){
        game->player->bag.potion ++;
        actionreload (game,0,0,'n');
    }
    if (drop_item == 0){
        if (l->m.mob_char == 'T'){
            if (game->player->classe.name == "Swordsman"){

            }
            if (game->player->classe.name == "Archer"){
                
            }
            if (game->player->classe.name == "Gunner"){
                
            }
            if (game->player->classe.name == "Viking"){
                
            }
        }
        if (l->m.mob_char == 'D'){
            if (game->player->classe.name == "Swordsman"){

            }
            if (game->player->classe.name == "Archer"){
                
            }
            if (game->player->classe.name == "Gunner"){
                
            }
            if (game->player->classe.name == "Viking"){
                
            }
        }
        if (l->m.mob_char == 'H'){
            if (game->player->classe.name == "Swordsman"){

            }
            if (game->player->classe.name == "Archer"){
                
            }
            if (game->player->classe.name == "Gunner"){
                
            }
            if (game->player->classe.name == "Viking"){
                
            }
        }
    }
    if (drop_potion == 0){
        if (l->m.mob_char == 'T'){
            if (game->player->classe.name == "Swordsman"){

            }
            if (game->player->classe.name == "Archer"){
                
            }
            if (game->player->classe.name == "Gunner"){
                
            }
            if (game->player->classe.name == "Viking"){
                
            }
        }
        if (l->m.mob_char == 'D'){
            if (game->player->classe.name == "Swordsman"){

            }
            if (game->player->classe.name == "Archer"){
                
            }
            if (game->player->classe.name == "Gunner"){
                
            }
            if (game->player->classe.name == "Viking"){
                
            }
        }
        if (l->m.mob_char == 'H'){
            if (game->player->classe.name == "Swordsman"){

            }
            if (game->player->classe.name == "Archer"){
                
            }
            if (game->player->classe.name == "Gunner"){
                
            }
            if (game->player->classe.name == "Viking"){
                
            }
        }
    }
}

void combat (Mob_list *l,Game game) {
    Mob_list *head;
    head = &(*l);
    int mob_money;
    srand (clock());
    while (*l) {
        if ((*l)->m.vida > 0) {
            if ((*l)->m.range >= abs((*l)->m.pos_x - game->player->p.x) && (*l)->m.range >= abs((*l)->m.pos_y - game->player->p.y)) {
                if ((*l)->m.dano - game->player->classe.defense >= 0) {
                    game->player->health -= ((*l)->m.dano - game->player->classe.defense);            }
            }
            if (game->player->classe.range >= abs((*l)->m.pos_x - game->player->p.x) && game->player->classe.range >= abs((*l)->m.pos_y - game->player->p.y)) {
                (*l)->m.vida -= game->player->classe.attack;
                if ((*l)->m.vida <= 0){
                    mob_money = rand()%11 + 5;
                    game->player->money += mob_money;
                    actionreload(game,5,0,(*l)->m.mob_char);
                    actionreload(game,1,mob_money,'n');
                    dropitem(game, l);
                } 
            }
        }
        l = &((*l)->prox);
    }
    l = head;
}

Mob_list create_mob2 (Map *m,int x,int y,int n,int floor,int diff) {
    int mx = (10*x)/9 - 25;
    Mob_list ml = malloc (sizeof(struct mob_list));
    if (floor == 1){
        return NULL;
    }
    Mob_list *temp = &ml;
    int i = 0;
    srand (clock());
    int tempy,tempx;
    while (i < n) {
        (*temp)->prox = malloc (sizeof(struct mob_list));
        tempy = tempx = -1;
        while (tempy == -1 || tempx == -1) {
            tempy = rand()%y;
            tempx = rand()%mx;
            if (m[tempy][tempx].walkable == false) {
                tempy = -1;
                tempx = -1;
            }
        }
        (*temp)->m.pos_x = tempx;
        (*temp)->m.pos_y = tempy;
        (*temp)->m.visible = false;
        int p = rand()%20;
        if (p < 9) {
            (*temp)->m.mob_char = 'D';
            (*temp)->m.dano = rand()%6 + 5 + (diff * 3);
            (*temp)->m.vida = 20;
            (*temp)->m.range = 3;
        }
        else {
            if (p >= 9 && p < 19-diff) {
                (*temp)->m.mob_char = 'T';
                (*temp)->m.dano = rand()%5 + 8 + (diff * 3);
                (*temp)->m.vida = 10;
                (*temp)->m.range = 2;
            }
            else if(p >= (19-diff)){
                (*temp)->m.mob_char = 'H';
                (*temp)->m.dano = rand()%11 + 15 + (diff * 3);
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