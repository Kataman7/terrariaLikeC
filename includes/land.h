#ifndef LAND_H
#define LAND_H

int* createAltitude(int length, int max_step);
void generateLand(struct Grid grid, int max_step);
void cleanLand(struct Grid grid);
void treeGeneration(struct Grid grid);

#endif
