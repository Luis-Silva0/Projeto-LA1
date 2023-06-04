#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "store.h"
#include "map.c"

LItems_s items_shop;

void openShop(Game game){
    WINDOW *win = newwin (16,70,game->maxY/2-7,game->maxX/2-35);
    int my, stop = 0, w = 0, a = 0, wt = 0, at = 0, p = 0;
    my = getmaxy (win);
    wattrset (win,COLOR_PAIR(2));
    char c = '0';
    while (stop == 0){
        wclear(win);
        box (win,'|','-');
        mvwprintw(win, 1, 1, "Potions -> x%d", game->player->bag.potion);
        mvwprintw(win, 2, 1, "Current Weapon -> %s + (%d)", game->player->bag.weapon->item, game->player->bag.weapon->enchantment);
        mvwprintw(win, 3, 1, "Current Armor -> %s + (%d)", game->player->bag.armor->item, game->player->bag.armor->enchantment);
        mvwprintw(win, 4, 1, "Gold -> %d", game->player->money);
        mvwprintw(win, 5, 1, "------------------------------For Sale------------------------------");
        if (w == 0){
            mvwprintw(win, 6, 3, "(y) %s + (%d)-> %d gold", items_shop->it_w->item, items_shop->it_w->enchantment, items_shop->it_w->price);
            mvwprintw(win, 7, 5, "Damage -> %d", (items_shop->it_w->value + items_shop->it_w->enchantment));
        }
        else if(w == 1){
            mvwprintw(win, 6, 3, "(y) Bought");
        }
        else {
            mvwprintw(win, 6, 3, "(y) Can't Purchase");
            w = wt;
        }
        if(a == 0){
            mvwprintw(win, 9, 3, "(u) %s + (%d)-> %d gold", items_shop->it_a->item, items_shop->it_a->enchantment, items_shop->it_a->price);
            mvwprintw(win, 10, 5, "Defense -> %d", (items_shop->it_a->value + items_shop->it_a->enchantment));
        }
        else if(a == 1){
            mvwprintw(win, 9, 3, "(u) Bought");
        }
        else {
            mvwprintw(win, 9, 3, "(u) Can't Purchase");
            a = at;
        }
        if (p == 0){
            mvwprintw(win, 12, 3, "Potions For Sale -> x%d (5 gold each)", items_shop->potions);
            mvwprintw(win, 13, 3, "(h)-> 1x, (j)-> 5x, (k)-> all");
        }
        else {
            mvwprintw(win, 12, 3, "(u) Can't Purchase");
            p = 0;
        }
        mvwprintw(win, my-2, 1, "Press (n) to leave");
        wrefresh(win);
        c = getchar();
        switch (c)
        {
        case 'y':
            if(game->player->money >= items_shop->it_w->price && w == 0){
                strcpy(game->player->bag.weapon->item, items_shop->it_w->item);
                game->player->bag.weapon->value = items_shop->it_w->value;
                game->player->bag.weapon->enchantment = items_shop->it_w->enchantment;
                game->player->bag.weapon->d = 1;
                game->player->money -= items_shop->it_w->price;
                w = 1;
            }
            else {
                wt = w;
                w = 2;
            }
            break;
        case 'u':
            if(game->player->money >= items_shop->it_a->price && a == 0){
                strcpy(game->player->bag.armor->item, items_shop->it_w->item);
                game->player->bag.armor->value = items_shop->it_a->value;
                game->player->bag.armor->enchantment = items_shop->it_a->enchantment;
                game->player->bag.armor->d = 2;
                game->player->money -= items_shop->it_a->price;
                a = 1;
            }
            else {
                at = a;
                a = 2;
            }
            break;
        case 'h':
            if (game->player->money >= 5 && items_shop->potions >= 1){
                game->player->bag.potion ++;
                items_shop->potions --;
                game->player->money -= 5;
            }
            else{
                p = 1;
            }
            break;
        case 'j':
            if (game->player->money >= 25 && items_shop->potions >= 5){
                game->player->bag.potion += 5;
                items_shop->potions -= 5;
                game->player->money -= 25;
            }
            else{
                p = 1;
            }
            break;
        case 'k':
            if (game->player->money >= items_shop->potions * 5 && items_shop->potions > 0){
                game->player->bag.potion += items_shop->potions;
                items_shop->potions = 0;
                game->player->money -= items_shop->potions * 5;
            }
            else{
                p = 1;
            }
            break;
        case 'n':
            stop = 1;
            break;
        default:
            break;
        }
        wrefresh(win);
    }
    delwin(win);

}

void createItems(Player player, int floor){
    items_shop = malloc(sizeof(struct litems_s));
    items_shop->it_w = malloc(sizeof(struct item_s));
    items_shop->it_a = malloc(sizeof(struct item_s));
    int rand_w, rand_a, num_p, rand_ench;
    rand_w = rand()%6;
    rand_a = rand()%6;
    num_p = rand()%11 + 5;
    rand_ench = rand()%5 + floor;
    items_shop->potions = num_p;

    if (strcmp(player.classe.name,"Swordsman") == 0){
        if (rand_w == 0){
            strcpy(items_shop->it_w->item, "Broadsword");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 13;
            items_shop->it_w->price = 25 + rand_ench*5;
        }
        else if (rand_w >= 4){
            strcpy(items_shop->it_w->item, "Zweihander");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 16;
            items_shop->it_w->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_w->item, "Master Sword");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 19;
            items_shop->it_w->price = 75 + rand_ench*5;
        }
        if(rand_a == 0){
            strcpy(items_shop->it_a->item, "Knight Set");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 9;
            items_shop->it_a->price = 25 + rand_ench*5;
        }
        else if (rand_a >= 4){
            strcpy(items_shop->it_a->item, "Royal Set");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 12;
            items_shop->it_a->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_a->item, "Hero Set");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 15;
            items_shop->it_a->price = 75 + rand_ench*5;
        }
    }
    if (strcmp(player.classe.name,"Archer") == 0){
        if (rand_w == 0){
            strcpy(items_shop->it_w->item, "Curved Bow");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 11;
            items_shop->it_w->price = 25 + rand_ench*5;
        }
        else if (rand_w >= 4){
            strcpy(items_shop->it_w->item, "Crossbow");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 14;
            items_shop->it_w->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_w->item, "Bow of Light");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 17;
            items_shop->it_w->price = 75 + rand_ench*5;
        }
        if(rand_a == 0){
            strcpy(items_shop->it_a->item, "Marksman Cloak");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 9;
            items_shop->it_a->price = 25 + rand_ench*5;
        }
        else if (rand_a >= 4){
            strcpy(items_shop->it_a->item, "Robin Hood's Cloak");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 12;
            items_shop->it_a->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_a->item, "Hunter's Set");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 15;
            items_shop->it_a->price = 75 + rand_ench*5;
        }
    }
    if (strcmp(player.classe.name,"Gunner") == 0){
        if (rand_w == 0){
            strcpy(items_shop->it_w->item, "Desert Eagle");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 7;
            items_shop->it_w->price = 25 + rand_ench*5;
        }
        else if (rand_w >= 4){
            strcpy(items_shop->it_w->item, "M16");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 10;
            items_shop->it_w->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_w->item, "AWP");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 13;
            items_shop->it_w->price = 75 + rand_ench*5;
        }
        if(rand_a == 0){
            strcpy(items_shop->it_a->item, "Navy Uniform");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 9;
            items_shop->it_a->price = 25 + rand_ench*5;
        }
        else if (rand_a >= 4){
            strcpy(items_shop->it_a->item, "Swat Uniform");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 12;
            items_shop->it_a->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_a->item, "Special Forces Uniform");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 15;
            items_shop->it_a->price = 75 + rand_ench*5;
        }
    }
    if (strcmp(player.classe.name,"Viking") == 0){
        if (rand_w == 0){
            strcpy(items_shop->it_w->item, "Iron Axe");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 19;
            items_shop->it_w->price = 25 + rand_ench*5;
        }
        else if (rand_w >= 4){
            strcpy(items_shop->it_w->item, "Battle Axe");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 22;
            items_shop->it_w->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_w->item, "Mjolnir");
            items_shop->it_w->enchantment = rand_ench;
            items_shop->it_w->value = 25;
            items_shop->it_w->price = 75 + rand_ench*5;
        }
        if(rand_a == 0){
            strcpy(items_shop->it_a->item, "Viking Armor");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 9;
            items_shop->it_a->price = 25 + rand_ench*5;
        }
        else if (rand_a >= 4){
            strcpy(items_shop->it_a->item, "Jormungandr's Skin");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 12;
            items_shop->it_a->price = 50 + rand_ench*5;
        }
        else{
            strcpy(items_shop->it_a->item, "Odin's Protection");
            items_shop->it_a->enchantment = rand_ench;
            items_shop->it_a->value = 15;
            items_shop->it_a->price = 75 + rand_ench*5;
        }
    }
}

Map* createshop (int x, int y, Player player, int floor){
    Map* mapa = calloc (y+1,sizeof(Map));
    for (int i = 0;i <= y;i++) {
        mapa[i] = calloc (x+1,sizeof(char)+sizeof(bool));
    }
    for (int i = 0;i <= y;i++) {
        for (int j = 0;j <= x;j++) {
            mapa[i][j].ch = ':';
            mapa[i][j].walkable = false;
        }
    }
    srand(clock ());
    int salas = 2, acc = 0;
    rooms = calloc (salas,4*sizeof(int));
    while (acc < salas){
        int bx, by, lx, ly;
        if (acc == 0){
            bx = 20;
            by = 8;
            lx = x - 44;
            ly = y - 20;
        }
        else{
            bx = x/2 - 14;
            by = y - 11;
            lx = 24;
            ly = 7;
        }
        rooms[acc].bx = bx;rooms[acc].by = by;rooms[acc].lx = lx;rooms[acc].ly = ly;
        for (int i = by;i < (by+ly);i++) {
            for (int j = bx;j < (bx+lx);j++) {
                mapa[i][j].ch = '#';
                mapa[i][j].walkable = false;
            }
        }
        acc++;
    }
    for (int i = 0;i < salas;i++) {
        for (int j = (1 + rooms[i].by);j < rooms[i].by + rooms[i].ly - 1;j++) {
            for (int k = (1 + rooms[i].bx);k < rooms[i].bx + rooms[i].lx - 1;k++) {
                mapa[j][k].ch = '.';
                mapa[j][k].walkable = true;
            }
        }
    }
    Position center1,center2;
    for (int i = 0;i < salas-1;i++) {
        center1.x = rooms[i].bx + rooms[i].lx/2;
        center1.y = rooms[i].by + rooms[i].ly/2;
        center2.x = rooms[i+1].bx + rooms[i+1].lx/2;
        center2.y = rooms[i+1].by + rooms[i+1].ly/2;
        ligasalas(center1,center2,mapa);
        if (i == 0){
            mapa[center1.y - 7][center1.x].ch = 'K';
            mapa[center1.y - 7][center1.x].walkable = false;
            mapa[center1.y][center1.x].ch = 'b';
            mapa[center1.y][center1.x].walkable = true;
        }
        if (i == salas-2) {
            mapa[center2.y][center2.x].ch = 's';
            mapa[center2.y][center2.x].walkable = true;
        }
    }
    createItems(player, floor);
    FILE *f;
    f = fopen("ASCIIart/Shop.txt","r");
    for (int i = 1;i < 7;i++) {
        for (int j = x/2-15;j < x/2+15;j++) {
            char c = fgetc (f);
            mapa[i][j].ch = c;
            mapa[i][j].walkable = false;
        }
        mapa[i][(x/2+14)].ch = ' ';
    }
    fclose (f);
    return mapa;

    // +5 gold per level of enchantment;
    // 4 items -> potions, 1 item from thralls (25 gold base), 1 from dreggs (50 gold base) and 1 from hydras (75 gold base);
    // enchantment = floor + rand() % 4;
}
