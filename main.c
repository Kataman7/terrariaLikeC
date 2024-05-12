#include <stdio.h>
#include <stdlib.h>
#include "includes/chunk.h"
#include "raylib.h"
#include "includes/land.h"
#include "includes/block.h"
#include "includes/cave.h"
#include "includes/player.h"
#include "time.h"

int main() {

    unsigned int seed = (unsigned int)time(NULL);
    printf("Seed: %u\n", seed);
    srand(seed);

    struct Grid grid = createGrid(40 * 6, 40 * 6);
    int blockSize = 45;
    double chanceToLive = 0.45;
    //caveGeneration(grid, chanceToLive);
    generateLand(grid, 10);

    const int screenWidth = 40 * blockSize;
    const int screenHeight = 20 * blockSize;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "TerrariaLike");

    Texture2D* textures = createTexture();

    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((float)grid.width/2)*(float)blockSize, ((float)grid.height/2)*(float)blockSize };
    camera.zoom = 1.0f;

    struct Player player = {
            camera.target.x,
            camera.target.y,
            0.5f,
    };

    double lastTime2 = GetTime();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        float zoomSpeed = 0.1f;
        float newZoom = camera.zoom - GetMouseWheelMove() * zoomSpeed;
        if (newZoom > 0.1f && newZoom < 5.0f && newZoom != camera.zoom) {
            camera.zoom = newZoom;
        }

        float speed = (float) blockSize * GetFrameTime() * 30;

        cameraControl(&camera, speed);
        gridEdit(grid, camera, blockSize);
        playerControl(grid, &player, blockSize);
        checkCollision(grid, player, blockSize);
        playerUpdate(grid, &player, blockSize, 0.001f);

        camera.target.x = player.x - (float) screenWidth / 2;
        camera.target.y = player.y - (float) screenHeight / 2;

        BeginMode2D(camera);

        updateTick(grid, &lastTime2, 0.5);
        displayGridImages3(grid, (float) blockSize, textures, camera);
        displayPlayer(player, blockSize);

        EndMode2D();

        DrawFPS(0, 0);

        EndDrawing();
    }

    unloadTexture(textures, 14);
    CloseWindow();
    free(textures);
    free(grid.list);

    return 0;
}