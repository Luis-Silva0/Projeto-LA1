#include "mobs.c"
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "map.h"
#include "play.h"

bool FOG_OF_WAR_ENABLED = true;

void actionreload (Game game, int n,int m,char c) {
    for (int i = 7;i > 0;i--) {
        strcpy (game->actions[i].line,game->actions[i-1].line);
        game->actions[i].color = game->actions[i-1].color;
    }
    if (n == 0) {
       strcpy (game->actions[0].line,"You got a potion");
       game->actions[0].color = 0;
    }
    else if (n == 1) {
        int d1 = m/10;
        int d2 = m%10;
        char s[21] = "You picked up ";
        s[14] = '0' + d1;
        s[15] = '0' + d2;
        s[16] = ' ';
        s[17] = 'g';
        s[18] = 'o';
        s[19] = 'l';
        s[20] = 'd';
        strcpy (game->actions[0].line,s);
        game->actions[0].color = 0;
    }
    else if (n == 2) {
        strcpy (game->actions[0].line,"You used a potion");
        game->actions[0].color = 1;
    }
    else if (n == 3) {
        strcpy (game->actions[0].line,"No potions left");
        game->actions[0].color = 2;
    }
    else if (n == 4) {
        if (c == 'D') {
            strcpy (game->actions[0].line,"You see a Dreg");
            game->actions[0].color = 2;
        }
        else if (c == 'T') {
            strcpy (game->actions[0].line,"You see a Thrall");
            game->actions[0].color = 2;
        }
        else if (c == 'H') {
            strcpy (game->actions[0].line,"You see a Hydra");
            game->actions[0].color = 2;
        }
        
    }
    else if (n == 5) {
        if (c == 'D') {
            strcpy (game->actions[0].line,"You killed a Dreg");
            game->actions[0].color = 0;
        }
        else if (c == 'T') {
            strcpy (game->actions[0].line,"You killed a Thrall");
            game->actions[0].color = 0;
        }
        else if (c == 'H') {
            strcpy (game->actions[0].line,"You killed a Hydra");
            game->actions[0].color = 0;
        }
    }
}

void actionShow (Game game) {
    int y = 11;
    for (int i = 0;i < 8;i++) {
        if (game->actions[i].line != NULL) {
            if (game->actions[i].color == 0) {
                attron (COLOR_PAIR(7));
                mvprintw (y,(game->maxX*10)/9 - 22, "%s",game->actions[i].line);
                attroff (COLOR_PAIR(7));
                y++;
            }
            else if (game->actions[i].color == 1) {
                mvprintw (y,(game->maxX*10)/9 - 22, "%s",game->actions[i].line);
                y++;
            }
            else if (game->actions[i].color == 2) {
                attron (COLOR_PAIR(8));
                mvprintw (y,(game->maxX*10)/9 - 22, "%s",game->actions[i].line);
                attroff (COLOR_PAIR(8));
                y++;
            }
        }
    }
}

void ligasalas (Position c1,Position c2,Map* m) {
    Position temp;
    temp.x = c1.x;
    temp.y = c1.y;
    srand(clock());
    while (true) {
        if (rand()%2 == 1) {
            if (abs((temp.x - 1) - c2.x) < abs(temp.x - c2.x)) {
                temp.x--;
            }
            else if (abs((temp.x + 1) - c2.x) < abs(temp.x - c2.x)) {
                temp.x++;
            }
            else if (abs((temp.y - 1) - c2.y) < abs(temp.y - c2.y)) {
                temp.y--;
            }
            else if (abs((temp.y + 1) - c2.y) < abs(temp.y - c2.y)) {
                temp.y++;
            }
            else break;
        }
        else {
            if (abs((temp.y - 1) - c2.y) < abs(temp.y - c2.y)) {
                temp.y--;
            }
            else if (abs((temp.y + 1) - c2.y) < abs(temp.y - c2.y)) {
                temp.y++;
            }
            else if (abs((temp.x - 1) - c2.x) < abs(temp.x - c2.x)) {
                temp.x--;
            }
            else if (abs((temp.x + 1) - c2.x) < abs(temp.x - c2.x)) {
                temp.x++;
            }
            else break;
        }
        m[temp.y][temp.x].ch = '.';
        m[temp.y][temp.x].walkable = true; 
        if (m[temp.y+1][temp.x-1].ch != '.') {
            m[temp.y+1][temp.x-1].ch = '#';
            m[temp.y+1][temp.x-1].walkable = false;
        }
         if (m[temp.y-1][temp.x+1].ch != '.') {
            m[temp.y-1][temp.x+1].ch = '#';
            m[temp.y-1][temp.x+1].walkable = false;
        }
         if (m[temp.y+1][temp.x+1].ch != '.') {
            m[temp.y+1][temp.x+1].ch = '#';
            m[temp.y+1][temp.x+1].walkable = false;
        }
         if (m[temp.y-1][temp.x-1].ch != '.') {
            m[temp.y-1][temp.x-1].ch = '#';
            m[temp.y-1][temp.x-1].walkable = false;
        }
    }
}

Map* createmap (int x, int y) {
    int mx = (x*10)/9 - 25;
    Map* mapa = calloc (y+1,sizeof(Map));
    for (int i = 0;i <= y;i++) {
        mapa[i] = calloc (mx+1,sizeof(char)+sizeof(bool));
    }
    for (int i = 0;i <= y;i++) {
        for (int j = 0;j <= mx;j++) {
            mapa[i][j].ch = ':';
            mapa[i][j].walkable = false;
        }
    }
    srand(clock ());
    int salas = (rand() % 10) + 11;
    int acc = 0;
    rooms = calloc (salas,4*sizeof(int));
    while (salas > acc) {
        int bx,by,lx,ly;
        lx = (rand() % (int)(mx*0.15)) + 6;
        ly = (rand() % (int)(y*0.15)) + 6;
        bx = (rand() % (mx-2)) + 1;
        by = (rand() % (y-2)) + 1;
        if (bx + lx >= mx) bx = bx - lx;
        if (by + ly >= y) by = by - ly;
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
                if (rand()%10 != 1) {
                    mapa[j][k].ch = '.';
                    mapa[j][k].walkable = true;
                }
                else {
                    mapa[j][k].ch = '+';
                    mapa[j][k].walkable = true;
                }
            }
        }
    }
/*    for (int i = 0; i < salas; i++){
        int num_mob = rand()%3;
        while (num_mob != 0){
            int fog = 1;
            int randx, randy;
            randx = (rand()%(rooms[i].lx-1)) + rooms[i].bx + 1;
            randy = (rand()%(rooms[i].ly-1)) + rooms[i].by + 1;
            if (mapa[randy][randx].ch == '.' || mapa[randy][randx].ch == '+'){
                create_mob(randy, randx, mapa, fog);
            }
            num_mob--;
        }
    }*/
    Position center1,center2;
    for (int i = 0;i < salas-1;i++) {
        center1.x = rooms[i].bx + rooms[i].lx/2;
        center1.y = rooms[i].by + rooms[i].ly/2;
        center2.x = rooms[i+1].bx + rooms[i+1].lx/2;
        center2.y = rooms[i+1].by + rooms[i+1].ly/2;
        ligasalas(center1,center2,mapa);
        if (i == salas-2) {
            mapa[center1.y][center1.x].ch = 's';
            mapa[center2.y][center2.x].walkable = true;
        }
    }
    return mapa;
}

void printTile(Game game, int y, int x) {
    if (game->map[y][x].ch == '#') {
        attrset(COLOR_PAIR(1));
        mvprintw(y, x, "%c", game->map[y][x].ch);
    }
    else if (game->map[y][x].ch == 's'){
        attrset(COLOR_PAIR(3));
        mvprintw(y, x, "%c", game->map[y][x].ch);
    }
    else if (game->map[y][x].ch == ':'){
        attrset(COLOR_PAIR(5));
        mvprintw(y, x, "%c", game->map[y][x].ch);
    }
    else{
        attrset(COLOR_PAIR(2));
        mvprintw(y, x, "%c", game->map[y][x].ch);
    }
}

void printVisible(Game game, float y, float x) {
    int i;
    float ox,oy;

    oy = (float)game->player->p.y+0.5f;
    ox = (float)game->player->p.x+0.5f;

    for(i = 0; i < 10; i++) {
        int ioy = (int)oy;
        int iox = (int)ox;

        printTile(game, ioy, iox);

        if (game->map[ioy][iox].ch == '#') {
            attrset(COLOR_PAIR(1));

            if (ioy+1 <= game->maxY && game->map[ioy+1][iox].ch == '#') {
                mvprintw(ioy+1, iox, "%c",'#');
            }
            if (ioy-1 >= 0 && game->map[ioy-1][iox].ch == '#') {
                mvprintw(ioy-1, iox, "%c",'#');
            }
            if (iox+1 <= game->maxX && game->map[ioy][iox+1].ch == '#') {
                mvprintw(ioy, iox+1, "%c",'#');
            }
            if (iox-1 >=0 && game->map[ioy][iox-1].ch == '#') {
                mvprintw(ioy, iox-1, "%c",'#');
            }
            return;
        }
        ox+=x;
        oy+=y;
    }
}

void printMap(Game game, int ps) {
    float x,y;
    int mx = (10*game->maxX)/9 - 25;
    int i;
    int sx = 0; 
    int sy = 0;
    if (ps > 0){
        game->godMode = true;
    }
    for (int i = 0; i < game->maxY; i++) {
        for (int j = 0; j < game->maxX; j++) {
            if (game->map[i][j].ch == 's'){
                sx = j;
                sy = i;
            }
        }
    }
    if (game->godMode) {
        for (int i = 0; i < game->maxY; i++) {
            for (int j = 0; j < mx; j++) {
                if (game->map[i][j].ch == '#'){
                    attrset(COLOR_PAIR(1));
                    mvprintw(i, j, "%c", game->map[i][j].ch);
                }
                else if (game->map[i][j].ch == 's'){
                    sx = j; 
                    sy = i;
                    attrset(COLOR_PAIR(3));
                    mvprintw(i, j, "%c", game->map[i][j].ch);
                    if (ps == 1){
                        game->player->p.x = j;
                        game->player->p.y = i-1;
                    }  
                }
                else if (game->map[i][j].ch == ':'){
                    attrset(COLOR_PAIR(5));
                    mvprintw(i, j, "%c", game->map[i][j].ch);
                }
                else if (game->map[i][j].ch != '.' && game->map[i][j].ch != '+'){
                        attrset(COLOR_PAIR(2));
                        attron (A_REVERSE);
                        mvprintw(i, j, "%c", game->map[i][j].ch);
                        attroff (A_REVERSE);
                }
                else {
                    attrset(COLOR_PAIR(2));
                    mvprintw(i, j, "%c", game->map[i][j].ch);
                }
            }
        }
    } else {
        for (i = 0; i < 360; i++) {
            y=sin((float)i*0.01745f);
            x=cos((float)i*0.01745f);
            printVisible(game, y, x);
        }
    }
    attrset(COLOR_PAIR(2));
    mvprintw(game->player->p.y, game->player->p.x, "%c", game->player->character);
    for(int i = 0; i < game->maxY; i++){
        mvprintw(i, (((game->maxX*10)/9) - 24), "|");
    }
    mvprintw(5, (((game->maxX*10)/9) - 23), "---------Exit---------");
    mvprintw(7, (((game->maxX*10)/9) - 17), "S -> %d %d", sx, sy);
    mvprintw(9, (((game->maxX*10)/9) - 23), "-------Actions:-------");
    mvprintw(20, (((game->maxX*10)/9) - 23), "-------Enemies:-------"); 
    mvprintw((game->maxY)-4,((game->maxX*10)/9) - 21, "Drink potion = (p)");
    mvprintw((game->maxY)-3,((game->maxX*10)/9) - 21, "Inventory = (i)");
    mvprintw((game->maxY)-2,((game->maxX*10)/9) - 21, "Help = (h)");
}


