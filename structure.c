#include "includes/chunk.h"
#include "includes/block.h"
#include "includes/structure.h"

void addStructure(struct Grid grid, struct Grid structure, int x, int y) {

    for (int i = 0; i < structure.height; ++i) {
        for (int j = 0; j < structure.width; ++j) {
            setCell(grid, x+j, y+i, getCell(structure, j, i));
        }
    }
    
}

struct Grid createStructure(int* pattern, int width, int height) {
    struct Grid grid = createGrid(width, height);

    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            setCell(grid, j, i, pattern[i * width + j]);
        }
    }

    return grid;
}

struct Grid createTree() {
    int treePatern[18] = {
            LEAVES_GREEN, LEAVES_GREEN, LEAVES_GREEN,
            LEAVES_GREEN, LEAVES_GREEN, LEAVES_GREEN,
            LEAVES_GREEN, LEAVES_GREEN, LEAVES_GREEN,
            VOID, TRUNK_PURPLE, VOID,
            VOID, TRUNK_PURPLE, VOID,
    };
    struct Grid tree = createStructure(treePatern, 3, 5);
    return tree;
}