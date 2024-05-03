#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/chunk.h"
#include "raylib.h"
#include "includes/land.h"
#include "includes/block.h"
#include "includes/cave.h"

int main() {

    unsigned int seed = (unsigned int)time(NULL);
    printf("Seed: %u\n", seed);
    srand(seed);

    struct Grid grid = createGrid(40 * 6, 40 * 6);
    int blockSize = 45;
    double chanceToLive = 0.45;
    //caveGeneration(grid, chanceToLive);
    generateLand(grid, 25);

    const int screenWidth = 40 * blockSize;
    const int screenHeight = 20 * blockSize;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "TerrariaLike");

    Texture2D* textures = createTexture();
    //UpdateTexture(textures[VINE - 1], "texture/vine.png");
    //UpdateTexture(textures[LEAVES_ORANGE - 1], "texture/lava.png");


    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((float)grid.width/2)*(float)blockSize, ((float)grid.height/2)*(float)blockSize };
    camera.zoom = 1.0f;

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

        float speed = (float) blockSize * GetFrameTime() * 30;

        if (IsKeyDown(KEY_LEFT_SHIFT)) (float) blockSize * 2 * GetFrameTime() * 15;

        if (IsKeyDown(KEY_UP)) camera.target.y -= speed;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += speed;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= speed;
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += speed;
        if (IsKeyPressed(KEY_SPACE)) generateLand(grid, 25);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
            int blockX = worldPos.x / blockSize;
            int blockY = worldPos.y / blockSize;
            setCell(grid, blockX, blockY, VOID);
        }
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
            int blockX = worldPos.x / blockSize;
            int blockY = worldPos.y / blockSize;
            setCell(grid, blockX, blockY, STONE);
        }

        BeginMode2D(camera);

        //nextVineGeneration(grid, &lastTime, 1);
        updateTick(grid, &lastTime2, 0.5);
        displayGridImages(grid, (float) blockSize, textures, camera);

        EndMode2D();

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
    free(textures);
    free(grid.list);

    return 0;
}