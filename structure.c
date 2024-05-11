#include "includes/chunk.h"
#include "includes/block.h"
#include "includes/structure.h"

void addStructure(struct Grid grid, struct Grid structure, int x, int y) {

    for (int i = 0; i < structure.height; ++i) {
        for (int j = 0; j < structure.width; ++j) {
            if (getCell(structure, j, i) != VOID)
                setCell(grid, x + j, y + i, getCell(structure, j, i));
        }
    }
}

struct Grid createStructure(int *pattern, int width, int height) {
    struct Grid grid = createGrid(width, height);

    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            setCell(grid, j, i, pattern[i * width + j]);
        }
    }

    return grid;
}

struct Grid createTree(int x) {
    int v = VOID;
    int l = LEAVES_GREEN;
    int t = TRUNK_PURPLE;

    if (rand() % 2 == 1) {
        l = LEAVES_ORANGE;
        t = TRUNK_BLUE;
    }


    int sizePatern0[2] = {3, 5};
    int treePatern0[3 * 5] = {
            v, l, v,
            l, l, l,
            l, l, l,
            v, t, v,
            v, t, v,
    };
    int sizePatern1[2] = {5, 7};
    int treePatern1[5 * 7] = {
            v, l, l, l, v,
            l, l, l, l, l,
            l, l, l, l, l,
            l, l, l, l, l,
            v, l, l, l, v,
            v, v, t, v, v,
            v, v, t, v, v
    };
    int sizePatern2[2] = {5, 6};
    int treePatern2[5 * 6] = {
            v, v, l, v, v,
            v, v, t, v, v,
            v, l, l, l, v,
            v, v, t, v, v,
            l, l, l, l, l,
            v, v, t, v, v
    };
    int *treePatern[3] = {
            treePatern0,
            treePatern1,
            treePatern2
    };
    int *sizePatern[3] = {
            sizePatern0,
            sizePatern1,
            sizePatern2
    };

    struct Grid tree = createStructure(treePatern[x], sizePatern[x][0], sizePatern[x][1]);
    return tree;
}