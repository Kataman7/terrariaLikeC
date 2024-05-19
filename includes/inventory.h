#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct {
    int id;
    int quantity;
} Item;

typedef struct {
    Item* items;
    int size;
} Inventory;

Inventory createInventory();
int addItem(Inventory* inventory, Item item);
int removeItem(Inventory* inventory, Item item);

#endif