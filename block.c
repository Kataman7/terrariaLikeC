#include <raylib.h>
#include "includes/block.h"
#include <stdlib.h>

Texture2D* createTexture() {
    Texture2D* textures = malloc(20 * sizeof(Texture2D));
    textures[STONE - 1] = LoadTexture("texture/stone.png");
    textures[MINERAL_PURPLE - 1] = LoadTexture("texture/mineral_purple.png");
    textures[MINERAL_BLACK - 1] = LoadTexture("texture/mineral_black.png");
    textures[VINE - 1] = LoadTexture("texture/vine.png");
    textures[STONE_GRASS - 1] = LoadTexture("texture/stone_grass.png");
    textures[STONE_DIRT - 1] = LoadTexture("texture/stone_dirt.png");
    textures[LEAVES_ORANGE - 1] = LoadTexture("texture/leaves_orange.png");
    textures[MINERAL_PINK - 1] = LoadTexture("texture/mineral_pink.png");
    textures[MINERAL_WHITE - 1] = LoadTexture("texture/mineral_white.png");
    textures[DIRT - 1] = LoadTexture("texture/dirt.png");
    textures[DIRT_GRASS - 1] = LoadTexture("texture/dirt_grass.png");
    textures[LEAVES_GREEN - 1] = LoadTexture("texture/leaves_green.png");
    textures[TRUNK_PURPLE - 1] = LoadTexture("texture/trunk_purple.png");
    return textures;
}