#include "raylib.h"
#include "includes/player.h"
#include "includes/chunk.h"
#include "includes/block.h"
#include "stdio.h"

struct Player createPlayer(float x, float y, int blockSize) {
    Rectangle hbox = {x, y, (float) (blockSize*0.95), (float) (blockSize*1.95)};
    struct Player player = {hbox, 0, 350, 0, 5, 0.45f};
    return player;
}

void mine(struct Player player, struct Grid grid, Camera2D camera, int blockSize) {
    Vector2 center = {player.entity.hidbox.x+player.entity.hidbox.width/2, player.entity.hidbox.y+player.entity.hidbox.height/2};

    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
    Vector2 blockPos = getBlockPosCliqued(camera, blockSize);
    Rectangle blockPosHB = {(float) ((int) blockPos.x * blockSize), (float) ((int) blockPos.y * blockSize), (float) blockSize, (float) blockSize };
    Rectangle cursor = {mousePos.x, mousePos.y, (float)blockSize/6, (float)blockSize/6};
    DrawRectangleRec(cursor, WHITE);

    if (CheckCollisionCircleRec(center, (float) (blockSize*player.entity.range), blockPosHB)) {
        Rectangle sourceRec = {
                0.0f,
                0.0f,
                (float) blocks[CURSOR].texture.width,
                (float) blocks[CURSOR].texture.height};
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(blocks[CURSOR].texture, sourceRec, blockPosHB, origin, 0.0f, WHITE);
        gridEdit(grid, camera, blockSize);
    }
}

void moveUpPlayer(struct Grid grid, struct Player* player, float gravity, int blockSize) {
    if (checkCollisionState(grid, player->entity, blockSize) == LADDER || checkCollisionState(grid, player->entity, blockSize) == LIQUID) {
        player->entity.velocity = -gravity * player->entity.jumpPower / 4;
    }
}

void playerControl(struct Grid grid, struct Player* player, float deltatime, float gravity, Camera2D camera, int blockSize) {
    if (IsKeyDown(KEY_UP)) moveUpPlayer(grid, player, gravity, blockSize);
    if (IsKeyPressed(KEY_UP)) moveUP( &player->entity, gravity);
    if (IsKeyDown(KEY_DOWN)) moveDown(&player->entity, deltatime);
    if (IsKeyDown(KEY_LEFT)) moveLeft(&player->entity, deltatime);
    if (IsKeyDown(KEY_RIGHT)) moveRight(&player->entity, deltatime);
    mine(*player, grid, camera, blockSize);
}

void cameraControl(Camera2D *camera, float speed) {
    if (IsKeyDown(KEY_UP)) camera->target.y -= speed;
    if (IsKeyDown(KEY_DOWN)) camera->target.y += speed;
    if (IsKeyDown(KEY_LEFT)) camera->target.x -= speed;
    if (IsKeyDown(KEY_RIGHT)) camera->target.x += speed;
}

void displayPlayer(struct Player player) {
    displayHidbox(player.entity, DARKBLUE);
}

void playerUpdate(struct Grid grid, struct Player *player, int blockSize, float gravity, float deltaTime, Camera2D camera) {

    float previousX = player->entity.hidbox.x;
    float previousY = player->entity.hidbox.y;

    player->entity.velocity += gravity * deltaTime;
    player->entity.hidbox.y += player->entity.velocity * deltaTime;

    Rectangle verticalCollision = checkCollision(grid, player->entity, blockSize);
    if (verticalCollision.x != 0) {
        if (player->entity.velocity > 0) player->entity.jumpCount = 0;
        player->entity.hidbox.y = previousY;
        player->entity.velocity = 0;
    }

    playerControl(grid, player, deltaTime, gravity, camera, blockSize);

    // collision horizontale après gestion des mouvements horizontaux
    Rectangle horizontalCollision = checkCollision(grid, player->entity, blockSize);
    if (horizontalCollision.x != 0) {
        player->entity.hidbox.x = previousX;
    }
}