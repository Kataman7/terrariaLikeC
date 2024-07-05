#include "includes/inventory.h"
#include "includes/block.h"
#include "stdlib.h"

Item *items = NULL;

void createItems() {
    int size = CURSOR + 2;
    items = malloc(size * sizeof(Item));
    for (int i = 0; i < size - 1; ++i) {
        Item item = {blocks[i].id, 1, blocks[i].texture};
        items[i] = item;
    }
}

Inventory createInventory() {
    int size = CURSOR;
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

int addItemInventoryQuantity(Inventory *inventory, Item item, int quantity) {
    item.quantity = quantity;
    return addItemInventory(inventory, item);
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
    return 0;
}

void moveSelectedRightInventory(Inventory *inventory) {
    inventory->selected--;
    if (inventory->selected < 0) inventory->selected = inventory->size-1;
}

void moveSelectedLeftInventory(Inventory *inventory) {
    inventory->selected++;
    if (inventory->selected >= inventory->size) inventory->selected = 0;
}

static int columns = 5;
void moveSelectedUpInventory(Inventory *inventory) {
    inventory->selected -= columns;
    if (inventory->selected < 0) {
        inventory->selected += inventory->size;
    }
}

void moveSelectedDownInventory(Inventory *inventory) {
    inventory->selected += columns;
    if (inventory->selected >= inventory->size) {
        inventory->selected -= inventory->size;
    }
}

int getSelectedItemId(Inventory inventory) {
    return inventory.items[inventory.selected].id;
}