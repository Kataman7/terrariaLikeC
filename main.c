#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"
#include "raylib.h"

int main() {

    struct Grid grid = createGrid(40 * 6, 20 * 6);
    int blockSize = 40;
    double chanceToLive = 0.45;
    caveGeneration(grid, chanceToLive);

    const int screenWidth = 40 * blockSize;
    const int screenHeight = 20 * blockSize;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "TerrariaLike");

    Texture2D textures[10];
    textures[0] = LoadTexture("texture/stone.png");
    textures[1] = LoadTexture("texture/mineral_purple.png");
    textures[2] = LoadTexture("texture/mineral_black.png");
    textures[3] = LoadTexture("texture/vine.png");
    textures[4] = LoadTexture("texture/stone_grass.png");
    textures[5] = LoadTexture("texture/stone_dirt.png");
    textures[6] = LoadTexture("texture/leaves_orange.png");
    textures[7] = LoadTexture("texture/mineral_pink.png");
    textures[8] = LoadTexture("texture/mineral_white.png");
    textures[9] = LoadTexture("texture/dirt.png");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((float)grid.width/2)*(float)blockSize, ((float)grid.height/2)*(float)blockSize };
    camera.zoom = 1.0f;

    double lastTime = GetTime();
    double lastTime2 = GetTime();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float zoomSpeed = 0.1f;
        float newZoom = camera.zoom - GetMouseWheelMove() * zoomSpeed;
        if (newZoom > 0.1f && newZoom < 5.0f && newZoom != camera.zoom) {
            camera.zoom = newZoom;
        }

        float speed = (float) blockSize * GetFrameTime() * 15;
        if (IsKeyDown(KEY_UP)) camera.target.y -= speed;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += speed;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= speed;
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += speed;
        if (IsKeyPressed(KEY_SPACE)) caveGeneration(grid, chanceToLive);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
            int blockX = worldPos.x / blockSize;
            int blockY = worldPos.y / blockSize;
            setCell(grid, blockX, blockY, 0);
        }

        BeginMode2D(camera);

        //nextVineGeneration(grid, &lastTime, 1);
        updateTick(grid, &lastTime2, 0.5);
        displayGridImages(grid, (float) blockSize, textures, camera);

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}