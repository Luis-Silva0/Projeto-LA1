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

int isPathClear(Game game, int x, int y) {
    float dx = (float)x - (float)game->player->p.x;
    float dy = (float)y - (float)game->player->p.y;
    float distance = sqrt(dx * dx + dy * dy);

    float stepX = dx / distance;
    float stepY = dy / distance;

    float currentX = (float)game->player->p.x + 0.5f;
    float currentY = (float)game->player->p.y + 0.5f;

    for (int i = 0; i < distance; i++) {
        int tileX = (int)currentX;
        int tileY = (int)currentY;

        if (game->map[tileY][tileX].ch == '#') {
            return 0;
        }

        currentX += stepX;
        currentY += stepY;
    }

    return 1;
}

int isMobVisible(Game game, int x, int y) {
    float dx = (float)x - (float)game->player->p.x;
    float dy = (float)y - (float)game->player->p.y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance <= 9.0f && !game->godMode) {
        return isPathClear(game, x, y);
    } else {
        return game->godMode;
    }
}

void show_mobs(Mob_list l, int x, Game game) {
    int y = 22;
    while (l) {
        if (l->m.vida > 0) {
            int tempx = l->m.pos_x;
            int tempy = l->m.pos_y;

            if (isMobVisible(game, tempx, tempy)) {
                mvprintw(y, x, "%c: %d %d %d", l->m.mob_char, tempx, tempy, l->m.vida);
                refresh();
                init_pair(4, COLOR_WHITE, COLOR_RED);
                attron(COLOR_PAIR(4));
                mvprintw(tempy, tempx, "%c", l->m.mob_char);
                attroff(COLOR_PAIR(4));
                if (game->godMode == true){
                    l->m.visible = true;
                }
                if (l->m.visible == false){
                    actionreload(game,4,0,l->m.mob_char);
                    l->m.visible = true;
                }
                refresh();
                y++;
            }
            else {
                l->m.visible = false;
            }
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
void addItem (LItems *li, Item i,int x,int y) {
    LItems *head = &(*li);
    while ((*li) != NULL) {
        li = &(*li)->prox;
    }
    (*li) = malloc (sizeof (struct litems)); 
    (*li)->it = malloc (sizeof(struct item));
    (*li)->prox = NULL;
    strcpy((*li)->it->item,i->item);
    (*li)->it->enchantment = i->enchantment;
    (*li)->it->value = i->value;
    (*li)->it->d = i->d;
    (*li)->x = x;
    (*li)->y = y;
    (*li)->it->visible = false;
    li = head;
}

void checkItem (Game game,LItems *items) {
    LItems *head = &(*items);
    while ((*items) != NULL) {
        if (isMobVisible (game,(*items)->x,(*items)->y)) {
            attron (COLOR_PAIR (13));
            if(game->godMode == true){
                (*items)->it->visible = true;
                if ((*items)->it->d == 1) mvprintw ((*items)->y,(*items)->x,"W");
                else mvprintw ((*items)->y,(*items)->x,"A");
            }
            else {
                if ((*items)->it->d == 1) {
                    if ((*items)->it->visible == false ) {
                        actionreload(game,7,0,'w');
                        (*items)->it->visible = true;
                    }
                    mvprintw ((*items)->y,(*items)->x,"W");
                }
                else {
                    if ((*items)->it->visible == false ) {
                        actionreload(game,7,0,'a');
                        (*items)->it->visible = true;
                    }
                    mvprintw ((*items)->y,(*items)->x,"A");
                }
            }
            attroff (COLOR_PAIR (13));
        }
        else (*items)->it->visible = false;
        if ((*items)->x == game->player->p.x && (*items)->y == game->player->p.y) {
            char temps[40];
            refresh();
            int x,y;
            int te,tv;
            te = tv = 0;
            getmaxyx (stdscr,y,x);
            WINDOW *win = newwin (18,70,y/2-8,x/2-35);
            mvwprintw (win,1,1,"Do you want to pick this up? (y/n)");
            mvwprintw (win,3,1,"%s",(*items)->it->item);
            mvwprintw (win,5,2,"Enchantment level: %d",(*items)->it->enchantment);
            mvwprintw (win,7,2,"Base value: %d", (*items)->it->value);
            if ((*items)->it->d == 1) {
                mvwprintw (win,11,1,"Previous item: %s",game->player->bag.weapon->item);
                mvwprintw (win,13,2,"Enchantment level: %d",game->player->bag.weapon->enchantment);
                mvwprintw (win,15,2,"Base value: %d",game->player->bag.weapon->value);
                box (win,0,0);
                wrefresh (win);
                delwin (win);
                char c = getchar ();
                switch (c)
                {
                case 'y':
                    strcpy(temps,game->player->bag.weapon->item);
                    te = game->player->bag.weapon->enchantment;
                    tv = game->player->bag.weapon->value;
                        
                    strcpy(game->player->bag.weapon->item,(*items)->it->item);
                    game->player->bag.weapon->enchantment = (*items)->it->enchantment;
                    game->player->bag.weapon->value = (*items)->it->value;
                        
                    strcpy((*items)->it->item,temps);
                    (*items)->it->enchantment = te;
                    (*items)->it->value = tv;
                    
                    break;
                
                default:
                    break;
                }
                
                refresh ();
            }
            else {
                mvwprintw (win,11,1,"Previous item: %s",game->player->bag.armor->item);
                mvwprintw (win,13,2,"Enchantment level: %d",game->player->bag.armor->enchantment);
                mvwprintw (win,15,2,"Base value: %d",game->player->bag.armor->value);
                box (win,0,0);
                wrefresh (win);
                delwin (win);
                char c = getchar ();
                switch (c)
                {
                case 'y':
                    strcpy(temps,game->player->bag.armor->item);
                    te = game->player->bag.armor->enchantment;
                    tv = game->player->bag.armor->value;
                        
                    strcpy(game->player->bag.armor->item,(*items)->it->item);
                    game->player->bag.armor->enchantment = (*items)->it->enchantment;
                    game->player->bag.armor->value = (*items)->it->value;
                        
                    strcpy((*items)->it->item,temps);
                    (*items)->it->enchantment = te;
                    (*items)->it->value = tv;
                    
                    break;
                
                default:
                    break;
                }
                
                refresh ();
                   
            }
        }
        items = &((*items)->prox);
    }
    items = head;
}

void dropitem (Game game, Mob_list *l,LItems *items, int diff){
    Item i = malloc (sizeof (struct item));
    srand(clock());
    int drop_potion = rand()%4;
    int drop_item = rand()%3;
    if (drop_potion != 0){
        game->player->bag.potion ++;
        actionreload (game,0,0,'n');
    }
    int d;
    d = rand() % 2 + 1;
    if (drop_item != 0){
        if (d == 1) actionreload (game,6,0,'w');
        else actionreload (game,6,0,'a');
        if ((*l)->m.mob_char == 'T'){
            if (strcmp (game->player->classe.name,"Swordsman") == 0){
                if (d == 1){
                    strcpy(i->item ,"Broadsword"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 13;
                }
                else{
                    strcpy(i->item ,"Knight Set");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 9;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Archer") == 0){
                if (d == 1){
                    strcpy(i->item ,"Curved Bow"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 11;
                }
                else{
                    strcpy(i->item ,"Marksman Cloak");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 6;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Gunner") == 0){
                if (d == 1){
                    strcpy(i->item ,"Desert Eagle"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 7;
                }
                else{
                    strcpy(i->item ,"Navy Uniform");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 6;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Viking") == 0){
                if (d == 1){
                    strcpy(i->item ,"Iron Axe"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 19;
                }
                else{
                    strcpy(i->item ,"Viking Armor");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 13;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
        }
        if ((*l)->m.mob_char == 'D'){
            if (strcmp (game->player->classe.name,"Swordsman") == 0){
                if (d == 1){
                    strcpy(i->item ,"Zweihander"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 16;
                }
                else{
                    strcpy(i->item ,"Royal Set");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 12;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Archer") == 0){
                if (d == 1){
                    strcpy(i->item ,"Crossbow"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 14;
                }
                else{
                    strcpy(i->item ,"Robin Hood's Cloak");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 9;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Gunner") == 0){
                if (d == 1){
                    strcpy(i->item ,"M16"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 10;
                }
                else{
                    strcpy(i->item ,"SWAT Uniform");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 9;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Viking") == 0){
                if (d == 1){
                    strcpy(i->item ,"Battle Axe"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 22;
                }
                else{
                    strcpy(i->item ,"Jormungandr's Skin");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 16;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
        }
        if ((*l)->m.mob_char == 'H'){
            if (strcmp (game->player->classe.name,"Swordsman") == 0){
                if (d == 1){
                    strcpy(i->item ,"Master Sword"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 19;
                }
                else{
                    strcpy(i->item ,"Hero Set");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 15;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Archer") == 0){
                if (d == 1){
                    strcpy(i->item ,"Bow of Light"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 17;
                }
                else{
                    strcpy(i->item ,"Hunter's Set");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 12;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Gunner") == 0){
                if (d == 1){
                    strcpy(i->item ,"AWP"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 13;
                }
                else{
                    strcpy(i->item ,"Special Forces Uniform");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 12;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
            if (strcmp (game->player->classe.name,"Viking") == 0){
                if (d == 1){
                    strcpy(i->item ,"Mjolnir"); 
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 25;
                }
                else{
                    strcpy(i->item ,"Odin's Protection");
                    i->enchantment = diff + rand () %5 - 2;
                    i->value = 19;
                }
                i->d = d;
                addItem(&(*items),i,(*l)->m.pos_x,(*l)->m.pos_y);
            }
        }
    }
}
/* das copy do nome do item*/
/* das o nivel do enchnatment*/
/* mandas base value*/
/*aqui escolhes 1 para armas e 2 para armaduras*/
/*aqui mandas a lista,o 'i' que é o item e manda o x e o y do mob que morreu para por lá o item*/

void combat (Mob_list *l,Game game,LItems *list, int diff) {
    Mob_list *head;
    head = &(*l);
    int mob_money;
    srand (clock());
    int defense, attack;
    defense = (game->player->bag.armor->value + game->player->bag.armor->enchantment) * 0.75;
    attack = (game->player->bag.weapon->value + game->player->bag.weapon->enchantment);
    while (*l) {
        if ((*l)->m.vida > 0) {
            if ((*l)->m.range >= abs((*l)->m.pos_x - game->player->p.x) && (*l)->m.range >= abs((*l)->m.pos_y - game->player->p.y) && (*l)->m.visible == true) {
                if ((*l)->m.dano - defense >= 0) {
                    game->player->health -= ((*l)->m.dano - defense);
                }
            }
            if (game->player->classe.range >= abs((*l)->m.pos_x - game->player->p.x) && game->player->classe.range >= abs((*l)->m.pos_y - game->player->p.y) && (*l)->m.visible == true) {
                (*l)->m.vida -= attack;
                if ((*l)->m.vida <= 0){
                    if ((*l)->m.mob_char == 'T'){
                        mob_money = rand()%11 + 5;
                    }
                    else if((*l)->m.mob_char == 'D'){
                        mob_money = rand()%11 + 10;
                    }
                    else{
                        mob_money = rand()%11 + 15;
                    }
                    game->player->money += mob_money;
                    actionreload(game,5,0,(*l)->m.mob_char);
                    actionreload(game,1,mob_money,'n');
                    dropitem(game, l,&(*list), diff);
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
    if (floor == 3){
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
            (*temp)->m.vida = 20 + (diff * 5);
            (*temp)->m.range = 3;
        }
        else {
            if (p >= 9 && p < 19-diff) {
                (*temp)->m.mob_char = 'T';
                (*temp)->m.dano = rand()%5 + 8 + (diff * 3);
                (*temp)->m.vida = 10 + (diff * 5);
                (*temp)->m.range = 2;
            }
            else if(p >= (19-diff)){
                (*temp)->m.mob_char = 'H';
                (*temp)->m.dano = rand()%11 + 15 + (diff * 3);
                (*temp)->m.vida = 50 + (diff * 5);
                (*temp)->m.range = 3;
            }
        }
    temp = &((*temp)->prox);
    i++;
    }
    *temp = NULL;
    return ml;
}