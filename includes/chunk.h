#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <raylib.h>

struct Grid {
    int width;
    int height;
    int *list;
};

struct ConwayRule {
    int min;
    int max;
    int birth;
};

struct Grid createGrid(int width, int height);
int getCell(struct Grid grid, int x, int y);
void setCell(struct Grid grid, int x, int y, int valeur);
int countNeighbor(struct Grid grid, int neighbor, int x, int y);
struct Grid createNeighborsGrid(struct Grid grid, int neighbor);
void nextCellularAutomataGeneration(struct Grid grid, int livingValue, int deadValue);
void randomGeneration(struct Grid grid, double chanceToLive, int livingValue, int deadValue, int conditionValue);
void printGrid(struct Grid grid);
void displayGridImages(struct Grid grid, float blockSize, Texture2D images[], Camera2D camera);
void nextConwayGeneration(struct Grid grid, struct ConwayRule rule, int livingValue, int deadValue);
int equalGrids(struct Grid grid1, struct Grid grid2);
struct Grid listNeighbor(struct Grid grid, int x, int y);
void cleanLava(struct Grid grid);
void displayGridImages3(struct Grid grid, float blockSize, Texture2D images[], Camera2D camera);
void gridEdit(struct Grid grid, Camera2D camera, int blockSize);



#endif
