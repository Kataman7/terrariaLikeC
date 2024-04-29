#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "chunk.h"
#include "raylib.h"

struct Grid createGrid(int width, int height) {
    struct Grid grid = {width, height, calloc(width * height, sizeof(int))};
    return grid;
}

int getCell(struct Grid grid, int x, int y) {
    if (x >= 0 && x < grid.width && y >= 0 && y < grid.height) return grid.list[y * grid.width + x];
    return 0;
}

void setCell(struct Grid grid, int x, int y, int valeur) {
    if (x >= 0 && x < grid.width && y >= 0 && y < grid.height) grid.list[y * grid.width + x] = valeur;
}

int countNeighbor(struct Grid grid, int neighbor, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Ne pas se compter
            int neighborX = x + i;
            int neighborY = y + j;

            // bord réfléchissant
            if (neighborX < 0) neighborX = -neighborX;
            if (neighborX >= grid.width) neighborX = 2 * grid.width - neighborX - 1;
            if (neighborY < 0) neighborY = -neighborY;
            if (neighborY >= grid.height) neighborY = 2 * grid.height - neighborY - 1;

            if (getCell(grid, neighborX, neighborY) == neighbor)
                count++;
        }
    }
    return count;
}

struct Grid listNeighbor(struct Grid grid, int x, int y) {
    struct Grid neighbors = createGrid(3, 3);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int neighborX = x + i;
            int neighborY = y + j;

            if (neighborX >= 0 && neighborX < grid.width && neighborY >= 0 && neighborY < grid.height) {
                setCell(neighbors, i + 1, j + 1, getCell(grid, neighborX, neighborY));
            }
        }
    }
    return neighbors;
}

int equalGrids(struct Grid grid1, struct Grid grid2) {
    if (grid1.width != grid2.width || grid1.height != grid2.height) return 0;
    for (int i = 0; i < grid1.height; ++i) {
        for (int j = 0; j < grid1.width; ++j) {
            if (getCell(grid1, j, i) != getCell(grid2, j, i)) return 0;
        }
    }
    return 1;
}

struct Grid createNeighborsGrid(struct Grid grid, int neighbor) {
    struct Grid neighborsGrid = {grid.width, grid.height, calloc(grid.width * grid.height, sizeof(int))};
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            setCell(neighborsGrid, j, i, countNeighbor(grid, neighbor, j, i));
        }
    }
    return neighborsGrid;
}

void nextCellularAutomataGeneration(struct Grid grid, int livingValue, int deadValue) {
    struct Grid neighborsGrid = createNeighborsGrid(grid, livingValue);
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            int neighbors = getCell(neighborsGrid, j, i);
            if (neighbors < 4 && getCell(grid, j, i) == livingValue) setCell(grid, j, i, deadValue);
            else if (neighbors >= 5 && getCell(grid, j, i) == deadValue) setCell(grid, j, i, livingValue);
        }
    }
    free(neighborsGrid.list);
}

void nextConwayGeneration(struct Grid grid, struct ConwayRule rule, int livingValue, int deadValue) {
    struct Grid neighborsGrid = createNeighborsGrid(grid, livingValue);
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            int neighbors = getCell(neighborsGrid, j, i);
            if (getCell(grid, j, i) == livingValue) {
                if (neighbors < rule.min || neighbors > rule.max) setCell(grid, j, i, deadValue);
            } else if (neighbors == rule.birth && getCell(grid, j, i) == deadValue) setCell(grid, j, i, livingValue);
        }
    }
    free(neighborsGrid.list);
}

void randomGeneration(struct Grid grid, double chanceToLive, int livingValue, int deadValue, int conditionValue) {
    srand(time(NULL));
    for (int i = 0; i < grid.height * grid.width; i++) {
        if (grid.list[i] == conditionValue || conditionValue == -1) {
            if (((double) rand() / RAND_MAX) > chanceToLive) grid.list[i] = deadValue;
            else grid.list[i] = livingValue;
        }
    }
}

void printGrid(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            printf("%i ", getCell(grid, j, i));
        }
    }
}

void displayGridRectangle(struct Grid grid, int blockSize) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            Color color = WHITE;
            if (getCell(grid, j, i) == 1) color = GRAY;
            else if (getCell(grid, j, i) == 2) color = BLUE;
            else if (getCell(grid, j, i) == 3) color = BLACK;
            else if (getCell(grid, j, i) == 4) color = GREEN;
            DrawRectangle(j * blockSize, i * blockSize, blockSize, blockSize, color);
        }
    }
}

void displayGridImages(struct Grid grid, float blockSize, Texture2D images[], Camera2D camera) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            // Calculate destination rectangle for the current grid cell
            Rectangle destRec = {(float) j * blockSize, (float) i * blockSize, blockSize, blockSize};

            // Check if the destination rectangle is visible in the camera view
            if (CheckCollisionRecs(destRec,
                                   (Rectangle) {camera.target.x - camera.offset.x, camera.target.y - camera.offset.y,
                                                GetScreenWidth(), GetScreenHeight()})) {
                int cellValue = getCell(grid, j, i);
                if (cellValue >= 1 && cellValue <= 10) {
                    Rectangle sourceRec = {0.0f, 0.0f, (float) images[cellValue - 1].width,
                                           (float) images[cellValue - 1].height};
                    Vector2 origin = {0.0f, 0.0f};
                    float rotation = 0.0f;
                    Color tint = WHITE;
                    DrawTexturePro(images[cellValue - 1], sourceRec, destRec, origin, rotation, tint);
                } else {
                    DrawRectangle(j * blockSize, i * blockSize, blockSize, blockSize, RAYWHITE);
                }
            }
        }
    }
}

void displayGridImages2(struct Grid grid, float blockSize, Texture2D images[], Camera2D camera) {

    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            int cellValue = getCell(grid, j, i);
            if (cellValue >= 1 && cellValue <= 6) {
                Rectangle sourceRec = {0.0f, 0.0f, (float) images[cellValue - 1].width,
                                       (float) -images[cellValue - 1].height};
                Rectangle destRec = {(float) j * blockSize, (float) i * blockSize, blockSize, blockSize};
                Vector2 origin = {0.0f, 0.0f};
                float rotation = 0.0f;
                Color tint = WHITE;
                DrawTexturePro(images[cellValue - 1], sourceRec, destRec, origin, rotation, tint);
            } else DrawRectangle(j * blockSize, i * blockSize, blockSize, blockSize, RAYWHITE);
        }
    }
}


void caveGeneration(struct Grid grid, double chanceToLive) {
    randomGeneration(grid, 0.5, 1, 0, -1);
    for (int i = 0; i < 10; ++i) {
        nextCellularAutomataGeneration(grid, 1, 0);
    }
    struct ConwayRule mineralRule = {1, 2, 3};
    struct ConwayRule stoneGrassRule = {1, 2, 3};
    struct ConwayRule stoneDirtRule = {1, 3, 2};

    generateMinerals(grid, mineralRule, 0.04, 2, 1);
    generateMinerals(grid, mineralRule, 0.07, 3, 1);
    //generateDirt(grid, 0.02, 10, 15);
    generateMinerals(grid, stoneGrassRule, 0.1, 5, 2);
    generateMinerals(grid, stoneDirtRule, 0.02, 6, 3);
    generateMinerals(grid, stoneDirtRule, 0.02, 8, 1);
    generateMinerals(grid, stoneDirtRule, 0.03, 9, 1);
    generateVine(grid);
    randomGeneration(grid, 0.005, 7, 0, 0);
}

void generateMinerals(struct Grid grid, struct ConwayRule rule, double chanceToLive, int mineralValue, int iteration) {
    randomGeneration(grid, chanceToLive, mineralValue, 1, 1);
    for (int i = 0; i < iteration; ++i) {
        nextConwayGeneration(grid, rule, mineralValue, 1);
    }
}

void generateDirt(struct Grid grid, double chanceToLive, int mineralValue, int iteration) {
    randomGeneration(grid, chanceToLive, mineralValue, 1, 1);
    struct Grid neighbors = createNeighborsGrid(grid, mineralValue);
    for (int a = 0; a < iteration; ++a) {
        for (int i = 0; i < grid.height; ++i) {
            for (int j = 0; j < grid.width; ++j) {
                if (getCell(grid, j, i) == 1) {
                    if (getCell(neighbors, j, i) >= 2) setCell(grid, j, i, mineralValue);
                }
                else if (getCell(grid, j, i) == mineralValue) {
                    if (getCell(neighbors, j, i) < 2) setCell(grid, j, i, 1);
                }
            }
        }
    }

    free(neighbors.list);
}

void generateVine(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            struct Grid neighbors = listNeighbor(grid, j, i);
            struct Grid pattern = createGrid(3, 3);
            setCell(pattern, 0, 0, 1);
            setCell(pattern, 1, 0, 1);
            setCell(pattern, 2, 0, 1);

            if (equalGrids(neighbors, pattern) == 1 && j % 2 == 0) setCell(grid, j, i, 4);

            free(neighbors.list);
            free(pattern.list);
        }
    }
}

void nextVineGeneration(struct Grid grid, struct Grid nextGrid, int x, int y) {
    if (getCell(grid, x, y) == 4) {
        if (getCell(grid, x, y - 1) == 0) setCell(nextGrid, x, y, -1);
        else if (getCell(grid, x, y + 1) == 0) setCell(nextGrid, x, y + 1, 4);
    }
}

void nextWaterGeneration(struct Grid grid, struct Grid nextGrid, int x, int y) {
    if (getCell(grid, x, y + 1) != 7) {
        if (countNeighbor(grid, 7, x, y) < 2 && countNeighbor(grid, 1, x, y ) < 2 && getCell(grid, x, y-1) != 7) setCell(nextGrid, x, y, -1);
        if (getCell(grid, x, y + 1) == 0) setCell(nextGrid, x, y + 1, 7);
        else {
            if (getCell(grid, x + 1, y) <= 0) setCell(nextGrid, x + 1, y, 7);
            if (getCell(grid, x - 1, y) <= 0) setCell(nextGrid, x - 1, y, 7);
        }
    }
}

void updateTick(struct Grid grid, double *lastTime, double tickTime) {
    if (GetTime() - *lastTime >= tickTime) {
        struct Grid nextGrid = createGrid(grid.width, grid.height);
        for (int i = 0; i < grid.height; ++i) {
            for (int j = 0; j < grid.width; ++j) {
                if (getCell(grid, j, i) == 4) nextVineGeneration(grid, nextGrid, j, i);
                else if (getCell(grid, j, i) == 7) nextWaterGeneration(grid, nextGrid, j, i);
            }
        }
        for (int i = 0; i < grid.height; ++i) {
            for (int j = 0; j < grid.width; ++j) {
                if (getCell(nextGrid, j, i) == 4) setCell(grid, j, i, 4);
                else if (getCell(nextGrid, j, i) == 7) setCell(grid, j, i, 7);
                else if (getCell(nextGrid, j, i) == -1) setCell(grid, j, i, 0);
            }
        }
        free(nextGrid.list);
        *lastTime = GetTime();
    }
}