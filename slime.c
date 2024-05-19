#include "includes/slime.h"
#include "includes/player.h"

struct Slime createSlime(float x, float y, int blockSize) {
    Rectangle hbox = {x, y, (float) (blockSize*0.95), (float) (blockSize*0.95)};
    Vector2 vector = {0};

    struct Entity entity = {
            hbox,
            0,
            200,
            0,
            10,
            0.3f
    };
    struct Slime slime = {
            entity,
            vector
    };
    return slime;
}

void slimeUpdate(struct Grid grid, struct Slime *monster, struct Player player, int blockSize, float gravity, float deltaTime) {

    float previousX = monster->entity.hidbox.x;
    float previousY = monster->entity.hidbox.y;

    monster->entity.velocity += gravity * deltaTime;
    monster->entity.hidbox.y += monster->entity.velocity * deltaTime;

    Rectangle verticalCollision = checkCollision(grid, monster->entity, blockSize);
    if (verticalCollision.x != 0) {
        monster->entity.hidbox.y = previousY;
        monster->entity.velocity = 0;
        monster->entity.jumpCount = 0;
    }

    slimeControl(grid, monster, player, deltaTime, gravity, blockSize);

    // collision horizontale après gestion des mouvements horizontaux
    Rectangle horizontalCollision = checkCollision(grid, monster->entity, blockSize);
    if (horizontalCollision.x != 0) {
        monster->entity.hidbox.x = previousX;
        moveUP((struct Entity *) monster, gravity);
    }
}

void slimeControl(struct Grid grid, struct Slime* monster, struct Player player, float deltatime, float gravity, int blockSize) {
    Vector2 center = {monster->entity.hidbox.x+monster->entity.hidbox.width/2, monster->entity.hidbox.y+monster->entity.hidbox.height/2};
    if (CheckCollisionCircleRec(center, (float) blockSize*monster->entity.range, player.entity.hidbox)) {
        if(monster->entity.hidbox.x < player.entity.hidbox.x) moveRight(&monster->entity, deltatime);
        else moveLeft((struct Entity *) monster, deltatime);
    }
}