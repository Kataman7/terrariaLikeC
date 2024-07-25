#include <stdio.h>
#include <stdlib.h>
#include "includes/chunk.h"
#include "raylib.h"
#include "includes/block.h"
#include "includes/land.h"
#include "includes/player.h"

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
            else if (neighbors > 4 && getCell(grid, j, i) == deadValue) setCell(grid, j, i, livingValue);
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

void displayGrid(struct Grid grid, float blockSize, Camera2D camera) {

    // Calculer les limites de la grille visible à l'écran
    Vector2 minScreen = GetScreenToWorld2D((Vector2){0, 0}, camera);
    Vector2 maxScreen = GetScreenToWorld2D((Vector2){(float) GetScreenWidth(), (float) GetScreenHeight()}, camera);

    // Convertir les limites de l'écran en coordonnées de grille
    int minX = (int)(minScreen.x / blockSize);
    int minY = (int)(minScreen.y / blockSize);
    int maxX = (int)(maxScreen.x / blockSize) + 1; // Ajouter 1 pour assurer le rendu complet du dernier bloc
    int maxY = (int)(maxScreen.y / blockSize) + 1;

    // Clipper les limites aux limites de la grille
    minX = MAX(0, minX);
    minY = MAX(0, minY);
    maxX = MIN(grid.width, maxX);
    maxY = MIN(grid.height, maxY);

    // Dessiner uniquement les blocs visibles à l'écran
    for (int i = minY; i < maxY; ++i) {
        for (int j = minX; j < maxX; ++j) {
            int cellValue = getCell(grid, j, i);
            if (cellValue != blocks[VOID].id) {
                drawBlock(j, i, blockSize, blocks[cellValue].texture);
            }
        }
    }
}

Vector2 getBlockPosCliqued(Camera2D camera, int blockSize) {
    Vector2 mousePos = GetMousePosition();
    Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
    Vector2 blockPos = {worldPos.x / (float) blockSize, worldPos.y / (float) blockSize};
    return blockPos;
}

void gridEdit(struct Grid grid, Camera2D camera, int blockSize, Inventory* inventory) {
    //if (IsKeyPressed(KEY_SPACE)) generateLand(grid, 25);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 blockPos = getBlockPosCliqued(camera, blockSize);
        addItemInventory(inventory, items[getCell(grid, blockPos.x, blockPos.y)]);
        setCell(grid, (int) blockPos.x, (int) blockPos.y, VOID);
    }
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        Vector2 blockPos = getBlockPosCliqued(camera, blockSize);
        // bug ici
        if (getCell(grid, blockPos.x, blockPos.y) != getSelectedItemId(*inventory) && getSelectedItemId(*inventory) != 0) {
            removeItemInventory(inventory, items[getSelectedItemId(*inventory)]);
            setCell(grid, (int) blockPos.x, (int) blockPos.y, getSelectedItemId(*inventory));
        }
    }
}

