#ifndef CAVE_H_INCLUDED
#define CAVE_H_INCLUDED

#include "chunk.h"

void generateVine(struct Grid grid);
void nextVineGeneration(struct Grid grid, struct Grid nextGrid, int x, int y);
void nextWaterGeneration(struct Grid grid, struct Grid nextGrid, int x, int y);
void updateTick(struct Grid grid, double *lastTime, double tickTime);
void generateDirt(struct Grid grid, double chanceToLive, int mineralValue, int iteration, int deadValue);
void caveGeneration(struct Grid grid);
void caveDecoration(struct Grid grid);
void generateMinerals(struct Grid grid, struct ConwayRule rule, double chanceToLive, int mineralValue, int iteration);
void cleanStone(struct Grid grid);

#endif