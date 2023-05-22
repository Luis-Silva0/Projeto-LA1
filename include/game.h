#ifndef GAME_H
#define GAME_H

#include "play.c"
//#include "map.c"
#include <ncurses.h>
#include <string.h>

// Map* mapa;

Player characterselect () {
    FILE *f;
    Player r;
    r.bag.armor = malloc (sizeof (struct item));
    r.bag.weapon = malloc (sizeof (struct item));
    int y,x,s = 1;
    getmaxyx (stdscr,y,x);   
    char c = 'r';
    while (s != 0) {
        erase ();
        mvprintw (1,(x/2)-13,"%s","Choose starting character:");
        mvprintw ((y/4)-5,(x/2)-13,"%s","Swordsman (s)");
        mvprintw ((2*y/4)-5,(x/2)-13,"%s","Archer (a)");
        mvprintw ((3*y/4)-5,(x/2)-13,"%s","Gunner (g)");
        mvprintw ((4*y/4)-5,(x/2)-13,"%s","Viking (v)");
        refresh ();
        while (c == 'r') {
            c = (char) getchar ();
            switch (c)
            {
            case 's':
                erase ();
                mvprintw ((y/2)-6,(x/2) - 32,"%s","Swordsman");
                f = fopen ("ASCIIart/sword.txt","r"); 
                char s[30][19];
                for (int i = 0;i < 30;i++) {
                    for (int j = 0;j < 19;j++) {
                        char c = (char) fgetc (f);
                        s[i][j] = c;
                    }
                }
                fclose (f);
                for (int i = 0;i < 30;i++) {
                    for (int j = 0;j < 19;j++) {
                        mvprintw (y-36+i,x-40+j,"%c",s[i][j]);
                    }
                }
            
                r.p.x = -1;
                r.p.y = -1;
                r.classe.name = "Swordsman";
                r.character = '@';
                r.health = 100;
                r.money = 0;
                r.classe.attack = 10;
                r.classe.defense = 6;
                r.classe.range = 2;
                r.bag.potion = 5;
                strcpy(r.bag.weapon->item ,"Basic Sword");
                strcpy(r.bag.armor->item ,"Iron Set");
                r.bag.weapon->value = r.classe.attack;
                r.bag.weapon->enchantment = 0;
                r.bag.armor->value = r.classe.defense;
                r.bag.armor->enchantment = 0;
                mvprintw ((y/2)-3,(x/2) - 29,"%s %d","Attack: ",r.classe.attack);
                mvprintw ((y/2),(x/2) - 29,"%s %d","Defense: ",r.classe.defense);
                mvprintw ((y/2)+3,(x/2) - 29,"%s %d","Range: ",r.classe.range);
                mvprintw (1,1,"%s","Press [BACKSPACE] to choose another character or any other key to continue");        
                break;

            case 'a':
                erase ();
                mvprintw ((y/2)-6,(x/2) - 32,"%s","Archer");
                f = fopen ("ASCIIart/bow_and_arrow.txt","r"); 
                char a[40][74];
                for (int i = 0;i < 40;i++) {
                    for (int j = 0;j < 74;j++) {
                        char c = (char) fgetc (f);
                        a[i][j] = c;
                    }
                }
                fclose (f);
                for (int i = 0;i < 40;i++) {
                    for (int j = 0;j < 74;j++) {
                        mvprintw (y-40+i,x-80+j,"%c",a[i][j]);
                    }
                }
            
                r.p.x = -1;
                r.p.y = -1;
                r.classe.name = "Archer";
                r.character = '@';
                r.health = 100;
                r.money = 0;
                r.classe.attack = 8;
                r.classe.defense = 3;
                r.classe.range = 4;
                r.bag.potion = 5;
                strcpy(r.bag.weapon->item ,"Basic Bow");
                strcpy(r.bag.armor->item ,"Cloak");
                r.bag.weapon->value = r.classe.attack;
                r.bag.weapon->enchantment = 0;
                r.bag.armor->value = r.classe.defense;
                r.bag.armor->enchantment = 0;
                mvprintw ((y/2)-3,(x/2) - 29,"%s %d","Attack: ",r.classe.attack);
                mvprintw ((y/2),(x/2) - 29,"%s %d","Defense: ",r.classe.defense);
                mvprintw ((y/2)+3,(x/2) - 29,"%s %d","Range: ",r.classe.range);
                mvprintw (1,1,"%s","Press [BACKSPACE] to choose another character or any other key to continue");        
                break;

            case 'g':
                erase ();
                mvprintw ((y/2)-6,(x/2) - 32,"%s","Gunner");
                f = fopen ("ASCIIart/gun.txt","r"); 
                char g[12][71];
                for (int i = 0;i < 12;i++) {
                    for (int j = 0;j < 71;j++) {
                        char c = (char) fgetc (f);
                        g[i][j] = c;
                    }
                }
                fclose (f);
                for (int i = 0;i < 12;i++) {
                    for (int j = 0;j < 71;j++) {
                        mvprintw (y-20+i,x-78+j,"%c",g[i][j]);
                    }
                }
            
                r.p.x = -1;
                r.p.y = -1;
                r.classe.name = "Gunner";
                r.character = '@';
                r.health = 100;
                r.money = 0;
                r.classe.attack = 4;
                r.classe.defense = 3;
                r.classe.range = 4;
                r.bag.potion = 5;
                strcpy(r.bag.weapon->item ,"Glock-17");
                strcpy(r.bag.armor->item ,"Military Uniform");
                r.bag.weapon->value = r.classe.attack;
                r.bag.weapon->enchantment = 0;
                r.bag.armor->value = r.classe.defense;
                r.bag.armor->enchantment = 0;
                mvprintw ((y/2)-3,(x/2) - 29,"%s %d","Attack: ",r.classe.attack);
                mvprintw ((y/2),(x/2) - 29,"%s %d","Defense: ",r.classe.defense);
                mvprintw ((y/2)+3,(x/2) - 29,"%s %d","Range: ",r.classe.range);
                mvprintw (1,1,"%s","Press [BACKSPACE] to choose another character or any other key to continue");        
                break;

            case 'v':
                erase ();
                mvprintw ((y/2)-6,(x/2) - 32,"%s","Viking");
                f = fopen ("ASCIIart/axe.txt","r"); 
                char v[18][64];
                for (int i = 0;i < 18;i++) {
                    for (int j = 0;j < 64;j++) {
                        char c = (char) fgetc (f);
                        v[i][j] = c;
                    }
                }
                fclose (f);
                for (int i = 0;i < 18;i++) {
                    for (int j = 0;j < 64;j++) {
                        mvprintw (y-20+i,x-78+j,"%c",v[i][j]);
                    }
                }
            
                r.p.x = -1;
                r.p.y = -1;
                r.classe.name = "Viking";
                r.character = '@';
                r.health = 1000;
                r.money = 0;
                r.classe.attack = 16;
                r.classe.defense = 10;
                r.classe.range = 2;
                r.bag.potion = 5;
                strcpy(r.bag.weapon->item ,"Basic Axe");
                strcpy(r.bag.armor->item ,"Viking Cloths");
                r.bag.weapon->value = r.classe.attack;
                r.bag.weapon->enchantment = 0;
                r.bag.armor->value = r.classe.defense;
                r.bag.armor->enchantment = 0;
                mvprintw ((y/2)-3,(x/2) - 29,"%s %d","Attack: ",r.classe.attack);
                mvprintw ((y/2),(x/2) - 29,"%s %d","Defense: ",r.classe.defense);
                mvprintw ((y/2)+3,(x/2) - 29,"%s %d","Range: ",r.classe.range);
                mvprintw (1,1,"%s","Press [BACKSPACE] to choose another character or any other key to continue");        
                break;
        
            default:
                c = 'r';
                break;
            }
        }
        refresh ();
        char p = (char)getchar ();
        if (p == 8 || p == 127) {
            c = 'r';
        }
        else s = 0;
    }
    return r;
}

void game () {
    Player player = characterselect ();
    int y,x,tx,floor,c,diff;
    floor = 0;
    diff = 0;
    curs_set(0);
    getmaxyx (stdscr,y,x);
    tx = x;
    x-=(x/10);
    while (floor < 7) {
        erase ();
        if (floor == 1){
            mapa = createshop (x,y);
        }
        else{
            mapa = createmap (x,y);
            diff++;
        }
        c = play (mapa,x,y,&player,floor,diff);
        if (c == 1) {
            floor++;
        }
        else {
            if (c == 0) {
            erase ();
            mvprintw (y/2,(tx/2)-9,"%s","You Died");
            mvprintw ((y/2)+1,(tx/2)-16,"%s","Press any key to leave");
            refresh();
            }
            else {
            erase ();
            mvprintw (y/2,(tx/2)-4,"%s","You ragequitted?");
            mvprintw ((y/2)+1,(tx/2)-18,"%s","Press any key to be stupid somewhere else...");
            refresh();
            }
            break;
        }
    }
    if (floor == 7 && c == 1) {
        erase ();
        mvprintw (y/2-1,tx/2-5,"Game Over");
        mvprintw (y/2,tx/2-9,"Thanks for playing");
        refresh ();
    }
    getchar ();
}



#endif
