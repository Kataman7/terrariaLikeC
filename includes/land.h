#ifndef LAND_H
#define LAND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chunk.h"

int* createAltitude(int length, int max_step);
void generateLand(struct Grid grid, int max_step);
void cleanLand(struct Grid grid);
void treeGeneration(struct Grid grid);

#endif
