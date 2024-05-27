#include "includes/inventory.h"
#include "includes/block.h"
#include "stdlib.h"

Item *items = NULL;

void createItems() {
    items = malloc(50 * sizeof(Item));
    for (int i = 0; i < CURSOR - 1; ++i) {
        Item item = {blocks[i].id, 1, blocks[i].texture};
        items[i] = item;
    }
}

Inventory createInventory() {
    int size = 20;
    Item *items = malloc(size * sizeof(Item));
    Inventory inventory = {items, size, 0};
    for (int i = 0; i < size; ++i) {
        Item vide = {0, 0};
        inventory.items[i] = vide;
    }
    return inventory;
}

int addItemInventory(Inventory *inventory, Item item) {
    if (item.id == 0) return 0;
    for (int i = 0; i < inventory->size; ++i) {
        if (inventory->items[i].id == item.id) {
            inventory->items[i].quantity++;
            return 1;
        }
    }
    for (int i = 0; i < inventory->size; ++i) {
        if (inventory->items[i].id == 0) {
            inventory->items[i] = item;
            return 1;
        }
    }
    return 0;
}

int removeItemInventory(Inventory *inventory, Item item) {
    for (int i = 0; i < inventory->size; ++i) {
        if (inventory->items[i].id == item.id) {
            inventory->items[i].quantity--;
            if (inventory->items[i].quantity <= 0) {
                inventory->items[i].id = 0;
                inventory->items[i].quantity = 0;
            }
            return 1;
        }
    }
    return 0; // Item non trouvé
}

void moveSelectedUpInventory(Inventory *inventory) {
    inventory->selected--;
    if (inventory->selected < 0) inventory->selected = inventory->size-1;
}

void moveSelectedDownInventory(Inventory *inventory) {
    inventory->selected++;
    if (inventory->selected >= inventory->size) inventory->selected = 0;
}

int getSelectedItemId(Inventory inventory) {
    return inventory.items[inventory.selected].id;
}