#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "play.h"

void check_inv (Player *p){
    int x,y;
    getmaxyx(stdscr,y,x);
    WINDOW *win = newwin (16,70,y/2-8,x/2-35);
    int my;
    my = getmaxy (win);
    wattrset(win,COLOR_PAIR(4));
    box (win,'|','-');
    wattrset (win,COLOR_PAIR(2));
    mvwprintw(win, 1, 1, "Potions -> x%d", p->bag.potion);
    mvwprintw(win, 2, 1, "Current Weapon -> %s", p->bag.weapon);
    mvwprintw(win, 3, 1, "Current Armor -> %s", p->bag.armor);
    mvwprintw(win, my-2, 1, "Press Any Key To Go Back.");
    wrefresh(win);
}