#ifndef GUI_H
#define GUI_H

#include "raylib.h"

#define GAMEGUI 0
#define INVENTORYGUI 1
#define ESCAPEGUI 2

void showInventory(Inventory inventory);
void guiControl();
void guiUpdate(struct Player player);

#endif
