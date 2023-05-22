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
    mvwprintw(win, 2, 1, "Current Weapon -> %s + (%d)", p->bag.weapon->item, p->bag.weapon->enchantment);
    mvwprintw(win, 3, 1, "Current Armor -> %s + (%d)", p->bag.armor->item, p->bag.armor->enchantment);
    mvwprintw(win, 4, 1, "----------------------------------------------------");
    mvwprintw(win, 5, 1, "Advanced Stats:");
    mvwprintw(win, 6, 1, "Damage -> %d", p->bag.weapon->value + p->bag.weapon->enchantment);
    mvwprintw(win, 7, 1, "Defense -> %d", p->bag.armor->value + p->bag.armor->enchantment);
    mvwprintw(win, 8, 1, "Range -> %d", p->classe.range);
    mvwprintw(win, my-2, 1, "Press Any Key To Go Back.");
    wrefresh(win);
}

void check_extrainfo (Game game) {
    WINDOW *win2 = newwin (16,70,game->maxY/2-8,game->maxX/2-35);
    int my;
    my = getmaxy(win2);
    wattrset(win2,COLOR_PAIR(4));
    box (win2,'|','-');
    wattrset (win2,COLOR_PAIR(4));
    mvwprintw (win2,2,3,"T");
    mvwprintw (win2,3,3,"D");
    mvwprintw (win2,4,3,"H");
    wattrset (win2,COLOR_PAIR(13));
    mvwprintw (win2,6,3,"W");
    mvwprintw (win2,7,3,"A");
    wattrset (win2,COLOR_PAIR(3));
    mvwprintw (win2,9,3,"s");
    wattrset (win2,COLOR_PAIR(2));
    mvwprintw (win2,2,4," -> Thrall: Melee Mob");
    mvwprintw (win2,3,4," -> Dreg: Ranged Mob");
    mvwprintw (win2,4,4," -> Hydra: Tank Mob");
    mvwprintw (win2,6,4," -> Weapon: New weapon dropped by mobs");
    mvwprintw (win2,7,4," -> Armor: New armor dropped by mobs");
    mvwprintw (win2,9,4," -> Stairs: Goes to next floor");
    mvwprintw(win2, my-2, 1, "Press Any Key To Go Back.");
    wrefresh (win2);
}