#include "includes/chunk.h"
#include "includes/block.h"
#include "includes/cave.h"
#include "stdlib.h"

void caveGeneration(struct Grid grid) {
    for (int i = 0; i < 10; ++i) {
        nextCellularAutomataGeneration(grid, STONE, VOID);
    }
}

void generateMinerals(struct Grid grid, struct ConwayRule rule, double chanceToLive, int mineralValue, int iteration) {
    randomGeneration(grid, chanceToLive, mineralValue, STONE, 1);
    for (int i = 0; i < iteration; ++i) {
        nextConwayGeneration(grid, rule, mineralValue, STONE);
    }
}

void generateDirt(struct Grid grid, double chanceToLive, int mineralValue, int iteration, int deadValue) {
    if (chanceToLive != 0) randomGeneration(grid, chanceToLive, mineralValue, deadValue, STONE);

    for (int a = 0; a < iteration; ++a) {
        struct Grid neighbors = createNeighborsGrid(grid, mineralValue);
        for (int i = 0; i < grid.height; ++i) {
            for (int j = 0; j < grid.width; ++j) {
                if (getCell(grid, j, i) == deadValue) {
                    if (getCell(neighbors, j, i) > 1) setCell(grid, j, i, mineralValue);
                }
                else if (getCell(grid, j, i) == mineralValue) {
                    if (getCell(neighbors, j, i) < 1) setCell(grid, j, i, deadValue);
                    else if (getCell(neighbors, j, i) > 9) setCell(grid, j, i, deadValue);
                }
            }
        }
        free(neighbors.list);
    }
}

void generateVine(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            struct Grid neighbors = listNeighbor(grid, j, i);
            struct Grid pattern = createGrid(3, 3);
            setCell(pattern, 0, 0, STONE);
            setCell(pattern, 1, 0, STONE);
            setCell(pattern, 2, 0, STONE);

            if (equalGrids(neighbors, pattern) == 1 && j % 2 == 0) setCell(grid, j, i, VINE);

            free(neighbors.list);
            free(pattern.list);
        }
    }
}

void nextVineGeneration(struct Grid grid, struct Grid nextGrid, int x, int y) {
    if (getCell(grid, x, y - 1) == VOID) setCell(nextGrid, x, y, -1);
    else if (getCell(grid, x, y + 1) == VOID) setCell(nextGrid, x, y + 1, VINE);
}

void nextWaterGeneration(struct Grid grid, struct Grid nextGrid, int x, int y) {
    if (getCell(grid, x, y + 1) != LAVA) {
        if ((countNeighbor(grid, LAVA, x, y) < 2) && countNeighbor(grid, STONE, x, y ) < 2 && getCell(grid, x, y-1) != LAVA) setCell(nextGrid, x, y, -1);
        if (getCell(grid, x, y + 1) == VOID) setCell(nextGrid, x, y + 1, LAVA);
        else {
            if (getCell(grid, x + 1, y) <= 0) setCell(nextGrid, x + 1, y, LAVA);
            if (getCell(grid, x - 1, y) <= 0) setCell(nextGrid, x - 1, y, LAVA);
        }
    }
}

void updateTick(struct Grid grid, double *lastTime, double tickTime) {
    if (GetTime() - *lastTime >= tickTime) {
        struct Grid nextGrid = createGrid(grid.width, grid.height);
        for (int i = 0; i < grid.height; ++i) {
            for (int j = 0; j < grid.width; ++j) {
                if (getCell(grid, j, i) == VINE) nextVineGeneration(grid, nextGrid, j, i);
                else if (getCell(grid, j, i) == LAVA) nextWaterGeneration(grid, nextGrid, j, i);
            }
        }
        for (int i = 0; i < grid.height; ++i) {
            for (int j = 0; j < grid.width; ++j) {
                if (getCell(nextGrid, j, i) == VINE) setCell(grid, j, i, VINE);
                else if (getCell(nextGrid, j, i) == LAVA) setCell(grid, j, i, LAVA);
                else if (getCell(nextGrid, j, i) == -1) setCell(grid, j, i, VOID);
            }
        }
        free(nextGrid.list);
        *lastTime = GetTime();
    }
}

void caveDecoration(struct Grid grid) {

    struct ConwayRule mineralRule = {1, 2, 3};
    struct ConwayRule stoneGrassRule = {1, 2, 3};
    struct ConwayRule stoneDirtRule = {1, 3, 2};
    struct ConwayRule maze = {1, 5, 3};

    //generateMinerals(grid, maze, 0.2, STONE_RED, 10);
    //cleanStone(grid);

    generateDirt(grid, 0.01, DIRT, 14, STONE);

    generateMinerals(grid, mineralRule, 0.04, MINERAL_PURPLE, 1);
    generateMinerals(grid, mineralRule, 0.07, MINERAL_BLACK, 1);

    generateMinerals(grid, stoneGrassRule, 0.1, STONE_GRASS, 2);
    generateMinerals(grid, stoneDirtRule, 0.02, STONE_DIRT, 3);

    generateMinerals(grid, stoneDirtRule, 0.02, MINERAL_WHITE, 1);
    generateMinerals(grid, stoneDirtRule, 0.03, MINERAL_PINK, 1);



    generateVine(grid);
    randomGeneration(grid, 0.005, LAVA, 0, 0);
}

void cleanLava(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            if (getCell(grid, j, i) == LAVA && countNeighbor(grid, STONE, j, i) < 1)
                setCell(grid, j, i, VOID);
        }
    }
}

void cleanStone(struct Grid grid) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            if (getCell(grid, j, i) == STONE && countNeighbor(grid, STONE_RED, j, i) > 4)
                setCell(grid, j, i, LEAVES_ORANGE);
        }
    }
}
