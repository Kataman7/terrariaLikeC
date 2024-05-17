#ifndef PLAYER_H
#define PLAYER_H

#include "chunk.h"
#include "raylib.h"
#include "entity.h"

struct Player {
    struct Entity entity;
};

void playerControl(struct Grid grid, struct Player* player, float deltatime, float gravity, Camera2D camera, int blockSize);
void displayPlayer(struct Player player);
void cameraControl(Camera2D *camera, float speed);
void playerUpdate(struct Grid grid, struct Player *player, int blockSize, float gravity, float deltaTime, Camera2D camera);
struct Player createPlayer(float x, float y, int blockSize);

#endif
