#ifndef INVENTORY_H
#define INVENTORY_H

#include "raylib.h"

typedef struct {
    int id;
    int quantity;
    Texture2D texture;
} Item;

typedef struct {
    Item* items;
    int size;
    int selected;
} Inventory;

extern Item* items;

Inventory createInventory();
int addItemInventory(Inventory* inventory, Item item);
int removeItemInventory(Inventory* inventory, Item item);
void createItems();
void moveSelectedUpInventory(Inventory *inventory);
void moveSelectedDownInventory(Inventory *inventory);
int getSelectedItemId(Inventory inventory);
void moveSelectedRightInventory(Inventory *inventory);
void moveSelectedLeftInventory(Inventory *inventory);

#endif