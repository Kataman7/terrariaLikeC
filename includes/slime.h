#ifndef MONSTER_H
#define MONSTER_H

#include "chunk.h"
#include "raylib.h"
#include "entity.h"
#include "player.h"

struct Slime {
    struct Entity entity;
    Vector2 target;
};

void slimeControl(struct Grid grid, struct Slime* slime, struct Player player, float deltatime, float gravity, int blockSize);
void slimeUpdate(struct Grid grid, struct Slime *slime, struct Player player, int blockSize, float gravity, float deltaTime);
struct Slime createSlime(float x, float y, int blockSize);


#endif