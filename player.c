#include "raylib.h"
#include "includes/player.h"
#include "includes/chunk.h"
#include "includes/block.h"
#include "stdio.h"

struct Player createPlayer(float x, float y, int blockSize) {
    Rectangle hbox = {x, y, (float) (blockSize*0.95), (float) (blockSize*1.95)};
    struct Player player = {hbox, 0, 350, 0, 6};
    return player;
}

Rectangle checkCollision(struct Grid grid, struct Player player, int blockSize) {

    float blockX = player.hidbox.x / (float) blockSize;
    float blockY = player.hidbox.y / (float) blockSize;

    for (int i = blockY-2; i < blockY+2; ++i) {
        for (int j = blockX-2; j < blockX+2; ++j) {
            if(getCell(grid, j, i) != 0) {

                Rectangle blockHB = {(float) (j*blockSize), (float) (i*blockSize), (float) blockSize, (float) blockSize};
                DrawRectangleRec(blockHB, RED);

                if (CheckCollisionRecs(blockHB, player.hidbox)) {
                    DrawRectangleRec(blockHB, GREEN);
                    return blockHB;
                }
            }
        }
    }

    Rectangle null = {0, 0, 0, 0};
    return null;
}


void mouveUP(struct Player* player, float gravity) {
    if (player->jumpCount == 0) {
        player->velocity = -gravity * 0.45;
        player->jumpCount ++;
    }
}

void mouveDown(struct Player* player, float deltaTime) {
}

void mouveLeft(struct Player* player, float deltaTime) {
    player->hidbox.x -= player->speed * deltaTime;
}

void mouveRight(struct Player* player, float deltaTime) {
    player->hidbox.x += player->speed * deltaTime;
}

void mine(struct Player player, struct Grid grid, Camera2D camera, int blockSize) {
    Vector2 center = {player.hidbox.x+player.hidbox.width/2, player.hidbox.y+player.hidbox.height/2};

    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
    Rectangle mouse = {mousePos.x, mousePos.y, 5, 5 };

    if (CheckCollisionCircleRec(center, (float) blockSize*player.range, mouse)) {
        gridEdit(grid, camera, blockSize);
    }
}

void playerControl(struct Grid grid, struct Player* player, float deltatime, float gravity, Camera2D camera, int blockSize) {
    if (IsKeyDown(KEY_UP)) mouveUP(player, gravity);
    if (IsKeyDown(KEY_DOWN)) mouveDown(player, deltatime);
    if (IsKeyDown(KEY_LEFT)) mouveLeft(player, deltatime);
    if (IsKeyDown(KEY_RIGHT)) mouveRight(player, deltatime);
    mine(*player, grid, camera, blockSize);
}

void cameraControl(Camera2D *camera, float speed) {
    if (IsKeyDown(KEY_UP)) camera->target.y -= speed;
    if (IsKeyDown(KEY_DOWN)) camera->target.y += speed;
    if (IsKeyDown(KEY_LEFT)) camera->target.x -= speed;
    if (IsKeyDown(KEY_RIGHT)) camera->target.x += speed;
}

void displayPlayer(struct Player player) {
    DrawRectangleRec(player.hidbox, DARKBLUE);
    //DrawRectangle(player.hidbox.x, player.hidbox.y, player.hidbox.width, player.hidbox.height, DARKBLUE);
}

void playerUpdate(struct Grid grid, struct Player *player, int blockSize, float gravity, float deltaTime, Camera2D camera) {

    float previousX = player->hidbox.x;
    float previousY = player->hidbox.y;

    player->velocity += gravity * deltaTime;
    player->hidbox.y += player->velocity * deltaTime;

    Rectangle verticalCollision = checkCollision(grid, *player, blockSize);
    if (verticalCollision.x != 0) {
        player->hidbox.y = previousY;
        player->velocity = 0;
        player->jumpCount = 0;
    }

    playerControl(grid, player, deltaTime, gravity, camera, blockSize);

    // collision horizontale après gestion des mouvements horizontaux
    Rectangle horizontalCollision = checkCollision(grid, *player, blockSize);
    if (horizontalCollision.x != 0) {
        player->hidbox.x = previousX;
    }
}