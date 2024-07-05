#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "stdlib.h"

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
#define LAVA_HEAD 25
#define LAVA_QUEUE 26
#define TRUNK_BLUE 15
#define TRUNK_YELLOW 16
#define TRUNK_MUSHROOM 17
#define STONE_BROKEN 18
#define STONE_RED 19
#define CHEST_PURPLE 20
#define CHEST_BLUE 21
#define WIRE 22
#define WIRE_QUEUE 23
#define WIRE_HEAD 24
#define CURSOR 27

//state
#define SOLID 0
#define LIQUID 1
#define LADDER 2

typedef struct {
    int id;
    int state;
    Texture2D texture;
} Block;

extern Block* blocks;
extern int blockSize;

Texture2D* createTexture();
void createBlocks();
void unloadTexture(int i);
void drawBlock(float x, float y, int blockSize, Texture2D texture);

#endif
