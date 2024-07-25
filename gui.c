#include "includes/inventory.h"
#include "raylib.h"
#include "includes/block.h"
#include "includes/player.h"
#include "includes/gui.h"

int currentGui = 0;

void showInventory(Inventory inventory) {

    Color transparentColor = (Color){BLACK.r, BLACK.g, BLACK.b, 128};
    int itemSize = blockSize * 1.5;
    Rectangle rectangle = {0, 0, itemSize * 5, itemSize * 5};
    DrawRectangleRec(rectangle, transparentColor);

    int counter = 0;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (counter < inventory.size) {
                if (inventory.items[counter].quantity != 0) {
                    drawBlock(j, i, itemSize, inventory.items[counter].texture);
                    DrawText(TextFormat("%i", inventory.items[counter].quantity), (j+0.5)*itemSize, (i+0.5)*itemSize, itemSize/2, BLACK);
                }
                if (counter == inventory.selected) drawBlock(j, i, itemSize, blocks[CURSOR].texture);
            }
            counter++;
        }
    }
}

void guiControl() {
    if (IsKeyPressed(KEY_E)) {
        if (currentGui == GAMEGUI) currentGui = INVENTORYGUI;
        else currentGui = GAMEGUI;
    }
}

void guiUpdate(struct Player player) {
    if (currentGui == INVENTORYGUI) showInventory(player.inventory);
}

void displayLoadingScreen(char* message) {
    ClearBackground(BLACK);
    DrawText(TextFormat(message), 100, 20, 20, WHITE);
}