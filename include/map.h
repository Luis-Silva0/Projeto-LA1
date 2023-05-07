#ifndef MAP_H
#define MAP_H

typedef struct pos {
    int y;
    int x;
} Position;
typedef struct map {
    char ch;
    bool walkable;
} *Map;

typedef struct sala {
    int bx,by,lx,ly;
} *Salas;
Salas rooms;
Map* mapa;

#endif //MAP_H
