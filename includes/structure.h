#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"
#include "block.h"

void addStructure(struct Grid grid, struct Grid structure, int x, int y);
struct Grid createStructure(int* pattern, int width, int height);
struct Grid createTree();

#endif
