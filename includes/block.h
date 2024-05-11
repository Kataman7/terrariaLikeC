#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

struct Block {
        int id,
        Texture2D 
};

#define VOID 0
#define STONE 1
#define STONE_GRASS 2
#define STONE_DIRT 3
#define MINERAL_BLACK 4
#define MINERAL_WHITE 5
#define MINERAL_PINK 6
#define MINERAL_PURPLE 7
#define DIRT 8
#define DIRT_GRASS 9
#define LEAVES_ORANGE 10
#define VINE 11
#define TRUNK_PURPLE 12
#define LEAVES_GREEN 13
#define LAVA 14
#define TRUNK_BLUE 15
#define TRUNK_YELLOW 16
#define TRUNK_MUSHROOM 17
#define STONE_BROKEN 18
#define STONE_RED 19


Texture2D* createTexture();
void unloadTexture(Texture2D* texture2D, int i);

#endif
