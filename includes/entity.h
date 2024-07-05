#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "chunk.h"

struct Entity {
    Rectangle hidbox;
    float velX;
    float velY;
    float speed;
    int jumpCount;
    int range;
    float jumpPower;
};

Rectangle checkCollision(struct Grid grid, struct Entity entity, int blockSize);
int checkCollisionState(struct Grid grid, struct Entity entity, int blockSize);
void moveUP(struct Entity* entity, float gravity);
void moveDown(struct Entity* entity, float deltaTime);
void moveLeft(struct Entity* entity, float deltaTime);
void moveRight(struct Entity* entity, float deltaTime);
void displayHidbox(struct Entity entity, Color color);

#endif