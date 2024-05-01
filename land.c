#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes/chunk.h"
#include "includes/block.h"
#include "includes/land.h"
#include "includes/cave.h"

#define sky 25

int *createAltitude(int length, int max) {
    int *terrain = malloc(length * sizeof(int));
    terrain[0] = rand() % (max + 1);

    for (int i = 1; i < length; i++) {
        int change = rand() % 3 - 1; // Génère -1, 0 ou 1
        terrain[i] = terrain[i-1] + change;

        if (terrain[i] > max) terrain[i] = max; // Limite supérieure
        else if (terrain[i] < -max) terrain[i] = -max; // Limite inférieure
    }
    return terrain;
}


void cleanLand(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {

            if (getCell(grid, j, i) == VOID && countNeighbor(grid, STONE, j, i) > 2 && countNeighbor(grid, DIRT, j, i) > 2)
                setCell(grid, j, i, STONE);
        }
    }
}

void generateLand(struct Grid grid, int max_step) {

    int *altitude = createAltitude(grid.width, 30);

    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            if (i == altitude[j]) setCell(grid, j, i+sky, DIRT_GRASS);
            else if (i > altitude[j] && i < altitude[j] + 2) setCell(grid, j, i+sky, DIRT);
            else if (i >= altitude[j] + 2 && i < altitude[j] + 5) setCell(grid, j, i+sky, STONE);
            else if (i >= altitude[j] + 5) {
                if (((double) rand() / RAND_MAX) > 0.5) setCell(grid, j, i+sky, VOID);
                else setCell(grid, j, i+sky, STONE);
            }
        }
    }

    caveGeneration(grid);
    cleanLand(grid);
    caveDecoration(grid);
    cleanLava(grid);

}

void treeGeneration(struct Grid grid) {
    srand(time(NULL));
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {

            struct Grid neighbors = listNeighbor(grid, j, i);

            struct Grid pattern = createGrid(3, 3);
            setCell(pattern, 0, 2, DIRT_GRASS);
            setCell(pattern, 1, 2, DIRT_GRASS);
            setCell(pattern, 2, 2, DIRT_GRASS);

            if (equalGrids(neighbors, pattern) == 1 && rand() % 2 == 0) {
                setCell(grid, j, i, TRUNK_PURPLE);
                setCell(grid, j, i - 1, TRUNK_PURPLE);
                setCell(grid, j, i - 2, LEAVES_GREEN);
            }

            free(neighbors.list);
            free(pattern.list);
        }
    }
}

