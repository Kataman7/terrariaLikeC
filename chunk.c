#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "includes/chunk.h"
#include "raylib.h"
#include "includes/block.h"

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
                if (cellValue >= 1 && cellValue <= 100) {
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


