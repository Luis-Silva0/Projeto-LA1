#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "play.h"

void check_inv (Player *p){
    WINDOW *win = newwin (15,70,20,80);
    int mx, my;
    getmaxyx(win, my, mx);
    box (win,'|','-');
    mvwprintw(win, 1, 1, "Potions -> x%d", p->bag.potion);
    mvwprintw(win, 2, 1, "Current Weapon -> %s", p->bag.weapon);
    mvwprintw(win, 3, 1, "Current Armor -> %s", p->bag.armor);
    mvwprintw(win, my-2, 1, "Press Any Key To Go Back.");
    wrefresh(win);
}