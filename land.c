#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes/chunk.h"
#include "includes/block.h"
#include "includes/land.h"
#include "includes/cave.h"
#include "includes/structure.h"

#define sky 10


int *createAltitude(int length, int max) {
    int *terrain = malloc(length * sizeof(int));
    terrain[0] = rand() % (max + 1);

    for (int i = 1; i < length;) {
        int mouvement = rand() % 3 - 1;
        int iteration = (rand() % 2) + 2;
        int y = 0;
        while (y < iteration && i < length) {
            terrain[i] = terrain[i - 1] + mouvement;
            printf("%i ", terrain[i]);

            if (terrain[i] < 0) terrain[i] = 0;
            else if (terrain[i] > max) terrain[i] = max;
            y++;i++;
        }
    }

    return terrain;
}



void cleanLand(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            if (getCell(grid, j, i) == VOID && countNeighbor(grid, STONE, j, i) > 2 &&
                countNeighbor(grid, DIRT, j, i) > 2)
                setCell(grid, j, i, STONE);

        }
    }
}

void generateLand(struct Grid grid, int max_step) {

    int *altitude = createAltitude(grid.width, 30);

    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            if (i < altitude[j] + 1) setCell(grid, j, i + sky, VOID);
            else if (i == altitude[j] + 1) setCell(grid, j, i + sky, DIRT_GRASS);
            else if (i > altitude[j] + 1 && i < altitude[j] + 3) setCell(grid, j, i + sky, DIRT);
            else if (i >= altitude[j] + 3 && i < altitude[j] + 6) setCell(grid, j, i + sky, STONE);
            else if (i >= altitude[j] + 5) {
                if (((double) rand() / RAND_MAX) > 0.5) setCell(grid, j, i + sky, VOID);
                else setCell(grid, j, i + sky, STONE);
            }
        }
    }

    caveGeneration(grid);
    cleanLand(grid);
    caveDecoration(grid);
    cleanLava(grid);
    treeGeneration(grid);
    free(altitude);
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
                struct Grid tree = createTree(rand() % 3);
                addStructure(grid, tree, j-tree.width/2, i-(tree.height-1));
            }

            free(neighbors.list);
            free(pattern.list);
        }
    }
}

