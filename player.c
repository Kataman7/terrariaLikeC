#include "raylib.h"
#include "includes/player.h"
#include "includes/chunk.h"
#include "stdio.h"

Rectangle checkCollision(struct Grid grid, struct Player player, int blockSize) {

    int blockX = player.x / blockSize;
    int blockY = player.y / blockSize;

    for (int i = blockY-3; i < blockY+3; ++i) {
        for (int j = blockX-3; j < blockX+3; ++j) {
            if(getCell(grid, j, i) != 0) {

                Rectangle blockHB = {j*blockSize, i*blockSize, blockSize, blockSize};
                Rectangle playerHB = {player.x, player.y, blockSize, blockSize};

                if (CheckCollisionRecs(blockHB, playerHB)) {
                    return blockHB;
                }
            }
        }
    }

    Rectangle null = {0, 0, 0, 0};
    return null;
}


void playerUpdate(struct Grid grid, struct Player* player, int blockSize, float gravity) {

    Rectangle blockHB = checkCollision(grid, *player, blockSize);

    if (blockHB.x != 0) {
        if (player->velocity < 0) {
            player->y = blockHB.y + blockHB.height;
        }
        else if (player->velocity > 0) {
            player->y = blockHB.y - (float) blockSize;
        }
        player->velocity = 0;
    }
    else {
        player->y += player->velocity;
        player->velocity += gravity;
    }
}




void mouveUP(struct Grid grid, struct Player* player, int blockSize) {
    player->velocity = -0.5f;
}

void mouveDown(struct Grid grid, struct Player* player, int blockSize) {
}

void mouveLeft(struct Grid grid, struct Player* player, int blockSize) {
    if (checkCollision(grid, *player, blockSize).x == 0) player->x -= 0.5f;
}

void mouveRight(struct Grid grid, struct Player* player, int blockSize) {
    if (checkCollision(grid, *player, blockSize).x == 0) player->x += 0.5f;
}

void playerControl(struct Grid grid, struct Player* player, int blockSize) {
    if (IsKeyDown(KEY_UP)) mouveUP(grid, player, blockSize);
    if (IsKeyDown(KEY_DOWN)) mouveDown(grid, player, blockSize);
    if (IsKeyDown(KEY_LEFT)) mouveLeft(grid, player, blockSize);
    if (IsKeyDown(KEY_RIGHT)) mouveRight(grid, player, blockSize);
}

void cameraControl(Camera2D *camera, float speed) {
    if (IsKeyDown(KEY_UP)) camera->target.y -= speed;
    if (IsKeyDown(KEY_DOWN)) camera->target.y += speed;
    if (IsKeyDown(KEY_LEFT)) camera->target.x -= speed;
    if (IsKeyDown(KEY_RIGHT)) camera->target.x += speed;
}

void displayPlayer(struct Player player, int blockSize) {
    DrawRectangle(player.x, player.y, blockSize, blockSize, WHITE);
}