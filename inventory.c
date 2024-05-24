#include "includes/inventory.h"
#include "stdlib.h"

Inventory createInventory() {
    int size = 20;
    Item* items = malloc(size * sizeof(Item));
    Inventory inventory = {items, size};
    for (int i = 0; i < size; ++i) {
        Item vide = {0, 0};
        inventory.items[i] = vide;
    }
    return inventory;
}

int addItem(Inventory* inventory, Item item) {
    int i = 0;
    for (;i < inventory->size; ++i) {
        if (inventory->items[i].id == 0) {
            inventory->items[i] = item;
            return 1;
        }
        if (inventory->items[i].id == item.id) {
            inventory->items[i].quantity++;
            return 1;
        }
    }
    return 0;
}

int removeItem(Inventory* inventory, Item item) {
    int i = 0;
    for (i; i < inventory->size; ++i) {
        if (inventory->items[i].id == item.id) {
            inventory->items[i].quantity--;
            if (inventory->items[i].quantity == 0) {
                inventory->items[i].id = 0;
                return 1;
            }
        }
    }
    return 0;
}

