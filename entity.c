#include "includes/entity.h"
#include "includes/chunk.h"
#include "raylib.h"
#include "includes/block.h"

Rectangle checkCollision(struct Grid grid, struct Entity entity, int blockSize) {

    float blockX = entity.hidbox.x / (float) blockSize;
    float blockY = entity.hidbox.y / (float) blockSize;

    for (int i = (int) blockY-2; (float) i < blockY+2; ++i) {
        for (int j = (int) blockX-2; (float) j < blockX+2; ++j) {
            if(getCell(grid, j, i) != VOID && blocks[getCell(grid, j, i)].state == SOLID) {

                Rectangle blockHB = {(float) (j*blockSize), (float) (i*blockSize), (float) blockSize, (float) blockSize};
                //DrawRectangleRec(blockHB, RED);

                if (CheckCollisionRecs(blockHB, entity.hidbox)) {
                    //DrawRectangleRec(blockHB, GREEN);
                    return blockHB;
                }
            }
        }
    }

    Rectangle null = {0, 0, 0, 0};
    return null;
}

int checkCollisionState(struct Grid grid, struct Entity entity, int blockSize) {
    float blockX = entity.hidbox.x / (float) blockSize;
    float blockY = entity.hidbox.y / (float) blockSize;
    for (int i = (int) blockY-2; (float) i < blockY+2; ++i) {
        for (int j = (int) blockX-2; (float) j < blockX+2; ++j) {
            if(getCell(grid, j, i) != VOID) {
                Rectangle blockHB = {(float) (j*blockSize), (float) (i*blockSize), (float) blockSize, (float) blockSize};
                if (CheckCollisionRecs(blockHB, entity.hidbox)) return blocks[getCell(grid, j, i)].state;
            }
        }
    }
    return -1;
}

void moveUP(struct Entity* entity, float gravity) {
    if (entity->jumpCount < 2) {
        entity->velY = -gravity * entity->jumpPower;
        entity->jumpCount ++;
    }
}

void moveDown(struct Entity* entity, float deltaTime) {
}

void moveLeft(struct Entity* entity, float deltaTime) {
    entity->hidbox.x -= entity->speed * deltaTime;
}

void moveRight(struct Entity* player, float deltaTime) {
    player->hidbox.x += player->speed * deltaTime;
}

void displayHidbox(struct Entity entity, Color color) {
    DrawRectangleRec(entity.hidbox, color);
}