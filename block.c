#include <raylib.h>
#include "includes/block.h"
#include <stdlib.h>
#include <stdio.h>

Texture2D* createTexture() {
    Texture2D* textures = malloc(20 * sizeof(Texture2D));
    textures[STONE - 1] = LoadTexture("texture/stone.png");
    textures[MINERAL_PURPLE - 1] = LoadTexture("texture/mineral_purple.png");
    textures[MINERAL_BLACK - 1] = LoadTexture("texture/mineral_black.png");
    textures[VINE - 1] = LoadTexture("texture/vine.png");
    textures[STONE_GRASS - 1] = LoadTexture("texture/stone_grass.png");
    textures[STONE_DIRT - 1] = LoadTexture("texture/stone_dirt.png");
    textures[MINERAL_PINK - 1] = LoadTexture("texture/mineral_pink.png");
    textures[MINERAL_WHITE - 1] = LoadTexture("texture/mineral_white.png");
    textures[DIRT - 1] = LoadTexture("texture/dirt.png");
    textures[DIRT_GRASS - 1] = LoadTexture("texture/dirt_grass.png");
    textures[LEAVES_GREEN - 1] = LoadTexture("texture/leaves_green.png");
    textures[LEAVES_ORANGE - 1] = LoadTexture("texture/leaves_orange.png");
    textures[TRUNK_PURPLE - 1] = LoadTexture("texture/trunk_purple.png");
    textures[LAVA - 1] = LoadTexture("texture/lava.png");
    textures[TRUNK_BLUE - 1] = LoadTexture("texture/trunk_blue.png");
    textures[TRUNK_YELLOW - 1] = LoadTexture("texture/trunk_yellow.png");
    textures[TRUNK_MUSHROOM - 1] = LoadTexture("texture/trunk_mushroom.png");
    textures[STONE_BROKEN - 1] = LoadTexture("texture/stone_broken.png");
    textures[STONE_RED - 1] = LoadTexture("texture/stone_red.png");

    return textures; // 14
}

void unloadTexture(Texture2D* texture2D, int i) {
    for (int j = 0; j < i; ++j) {
        UnloadTexture(texture2D[j]);
    }
}