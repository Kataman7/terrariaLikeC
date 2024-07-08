#include <raylib.h>
#include "includes/block.h"
#include <stdlib.h>

int blockSize = 45;

Block* blocks = NULL;

void createBlocks() {
    blocks = malloc(40 * sizeof(Block));
    blocks[VOID] = (Block){VOID, 0, LoadTexture("texture/stone.png")};
    blocks[STONE] = (Block){STONE, SOLID, LoadTexture("texture/stone.png")};
    blocks[STONE_GRASS] = (Block){STONE_GRASS, SOLID, LoadTexture("texture/stone_grass.png")};
    blocks[STONE_DIRT] = (Block){STONE_DIRT, SOLID, LoadTexture("texture/stone_dirt.png")};
    blocks[MINERAL_BLACK] = (Block){MINERAL_BLACK, SOLID, LoadTexture("texture/mineral_black.png")};
    blocks[MINERAL_WHITE] = (Block){MINERAL_WHITE, SOLID, LoadTexture("texture/mineral_white.png")};
    blocks[MINERAL_PINK] = (Block){MINERAL_PINK, SOLID, LoadTexture("texture/mineral_pink.png")};
    blocks[MINERAL_PURPLE] = (Block){MINERAL_PURPLE, SOLID, LoadTexture("texture/mineral_purple.png")};
    blocks[DIRT] = (Block){DIRT, SOLID, LoadTexture("texture/dirt.png")};
    blocks[DIRT_GRASS] = (Block){DIRT_GRASS, SOLID, LoadTexture("texture/dirt_grass.png")};
    blocks[LEAVES_ORANGE] = (Block){LEAVES_ORANGE, SOLID, LoadTexture("texture/leaves_orange.png")};
    blocks[VINE] = (Block){VINE, LADDER, LoadTexture("texture/vine.png")};
    blocks[TRUNK_PURPLE] = (Block){TRUNK_PURPLE, SOLID, LoadTexture("texture/trunk_purple.png")};
    blocks[LEAVES_GREEN] = (Block){LEAVES_GREEN, SOLID, LoadTexture("texture/leaves_green.png")};
    blocks[LAVA] = (Block){LAVA, LIQUID, LoadTexture("texture/lava.png")};
    blocks[LAVA_SOURCE] = (Block){LAVA_SOURCE, LIQUID, LoadTexture("texture/lava.png")};
    blocks[TRUNK_BLUE] = (Block){TRUNK_BLUE, SOLID, LoadTexture("texture/trunk_blue.png")};
    blocks[TRUNK_YELLOW] = (Block){TRUNK_YELLOW, SOLID, LoadTexture("texture/trunk_yellow.png")};
    blocks[TRUNK_MUSHROOM] = (Block){TRUNK_MUSHROOM, SOLID, LoadTexture("texture/trunk_mushroom.png")};
    blocks[STONE_BROKEN] = (Block){STONE_BROKEN, SOLID, LoadTexture("texture/stone_broken.png")};
    blocks[STONE_RED] = (Block){STONE_RED, SOLID, LoadTexture("texture/stone_red.png")};
    blocks[CHEST_PURPLE] = (Block){CHEST_PURPLE, SOLID, LoadTexture("texture/chest_purple.png")};
    blocks[CHEST_BLUE] = (Block){CHEST_BLUE, SOLID, LoadTexture("texture/chest_blue.png")};
    blocks[WIRE] = (Block){WIRE, SOLID, LoadTexture("texture/wire_off.png")};
    blocks[WIRE_QUEUE] = (Block){WIRE_QUEUE, SOLID, LoadTexture("texture/wire_off.png")};
    blocks[WIRE_HEAD] = (Block){WIRE_HEAD, SOLID, LoadTexture("texture/wire_on.png")};
    blocks[WATER] = (Block){WATER, LIQUID, LoadTexture("texture/water.png")};
    blocks[WATER_SOURCE] = (Block){WATER_SOURCE, LIQUID, LoadTexture("texture/water.png")};
    blocks[SAND] = (Block){SAND, SOLID, LoadTexture("texture/sand.png")};
    blocks[CURSOR] = (Block){CURSOR, 0, LoadTexture("texture/cursor.png")};
}

void unloadTexture(int i) {
    for (int j = 0; j < i; ++j) {
        UnloadTexture(blocks->texture);
    }
}

void drawBlock(float x, float y, int blockSize, Texture2D texture) {
    Rectangle destRec = {x * blockSize, y * blockSize, blockSize, blockSize};
    Rectangle sourceRec = { 0.0f,0.0f,(float) texture.width,(float) texture.height};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
}