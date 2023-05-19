#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "play.h"
#include "mobs2.c"

void check_info (Player *p){
    int x,y;
    getmaxyx(stdscr,y,x);
    WINDOW *win = newwin (16,70,y/2-8,x/2-35);
    int my;
    my = getmaxy (win);
    wattrset(win,COLOR_PAIR(4));
    box (win,'|','-');
    wattrset (win,COLOR_PAIR(2));
    mvwprintw(win, 1, 1, "Potions -> x%d", p->bag.potion);
    mvwprintw(win, 2, 1, "Current Weapon -> %s + %d", p->bag.weapon.item, p->bag.weapon.enchantment);
    mvwprintw(win, 3, 1, "Current Armor -> %s + %d", p->bag.armor.item, p->bag.weapon.enchantment);
    mvwprintw(win, 4, 1, "----------------------------------------------------");
    mvwprintw(win, 5, 1, "Advanced Stats:");
    mvwprintw(win, 6, 1, "Damage -> %d", p->bag.weapon.value);
    mvwprintw(win, 7, 1, "Defense -> %d", p->bag.armor.value);
    mvwprintw(win, 8, 1, "Range -> %d", p->classe.range);
    mvwprintw(win, my-2, 1, "Press Any Key To Go Back.");
    wrefresh(win);
}
void check_inv (Player *p){
    int x,y;
    getmaxyx(stdscr,y,x);
    WINDOW *win = newwin (16,70,y/2-8,x/2-35);
    int my, y_max;
    my = getmaxy (win);
    box (win,'|','-');
    y_max = update_inv();
}