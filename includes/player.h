#ifndef PLAYER_H
#define PLAYER_H

#include "chunk.h"
#include "raylib.h"

struct Player {
    Rectangle hidbox;
    float velocity;
    float speed;
    int jumpCount;
    int range;
};

void playerControl(struct Grid grid, struct Player* player, float deltatime, float gravity, Camera2D camera, int blockSize);
void displayPlayer(struct Player player);
void cameraControl(Camera2D *camera, float speed);
Rectangle checkCollision(struct Grid grid, struct Player player, int blockSize);
void playerUpdate(struct Grid grid, struct Player *player, int blockSize, float gravity, float deltaTime, Camera2D camera);
struct Player createPlayer(float x, float y, int blockSize);

#endif
