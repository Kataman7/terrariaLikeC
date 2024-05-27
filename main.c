#include <stdio.h>
#include <stdlib.h>
#include "includes/chunk.h"
#include "raylib.h"
#include "includes/land.h"
#include "includes/block.h"
#include "includes/cave.h"
#include "includes/player.h"
#include "time.h"
#include "includes/slime.h"
#include "includes/entity.h"
#include "includes/gui.h"

int main() {

    unsigned int seed = (unsigned int)time(NULL);
    printf("Seed: %u\n", seed);
    srand(seed);

    struct Grid grid = createGrid(40 * 6, 40 * 6);
    generateLand(grid, 10);

    const int screenWidth = 40 * blockSize;
    const int screenHeight = 20 * blockSize;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "TerrariaLike");
    HideCursor();

    SetTargetFPS( 500 );
    //SetTargetFPS( GetMonitorRefreshRate(GetCurrentMonitor()));

    //Texture2D* textures = createTexture();
    //blocks = malloc(20 * sizeof(Block));
    createBlocks();
    createItems();


    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((float)grid.width/2)*(float)blockSize, ((float)grid.height/2)*(float)blockSize };
    camera.zoom = 1.0f;

    struct Player player = createPlayer(camera.target.x, camera.target.y, blockSize);
    struct Slime monster = createSlime(camera.target.x, camera.target.y, blockSize);

    double lastTime2 = GetTime();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        /*
        float zoomSpeed = 0.1f;
        float newZoom = camera.zoom - GetMouseWheelMove() * zoomSpeed;
        if (newZoom > 0.1f && newZoom < 5.0f && newZoom != camera.zoom) {
            camera.zoom = newZoom;
        }
        */

        float speed = (float) blockSize * GetFrameTime() * 30;

        cameraControl(&camera, speed);

        camera.target.x = player.entity.hidbox.x - (float) screenWidth / 2;
        camera.target.y = player.entity.hidbox.y - (float) screenHeight / 2;

        BeginMode2D(camera);
        Color skyColor = {225,246,255};
        ClearBackground(skyColor);

        updateTick(grid, &lastTime2, 0.5);
        displayPlayer(player);
        displayHidbox(monster.entity, YELLOW);
        displayGrid(grid, (float) blockSize, camera);
        playerUpdate(grid, &player, blockSize, 3000, GetFrameTime(), camera);
        slimeUpdate(grid, &monster, player, blockSize, 3000, GetFrameTime());

        EndMode2D();

        guiControl();
        guiUpdate(player);
        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
    unloadTexture(CURSOR);
    free(blocks);
    free(grid.list);

    return 0;
}