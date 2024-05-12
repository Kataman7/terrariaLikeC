#ifndef PLAYER_H
#define PLAYER_H

#include "chunk.h"
#include "raylib.h"

struct Player {
    float x;
    float y;
    float velocity;
};

void playerControl(struct Grid grid, struct Player* player, int blockSize);
void displayPlayer(struct Player player, int blockSize);
//void gravity(struct Player* player, float gravity);
void cameraControl(Camera2D *camera, float speed);
Rectangle checkCollision(struct Grid grid, struct Player player, int blockSize);
void playerUpdate(struct Grid grid, struct Player* player, int blockSize, float gravity);

#endif
