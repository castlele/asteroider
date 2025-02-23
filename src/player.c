#include "player.h"
#include "raylib.h"
#include "raymath.h"

void PlayerUpdate(Player *player)
{
    float dt = GetFrameTime();

    int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    player->rotation -= xIn * PLAYER_ROT_SPEED * dt;

    // int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);

    // TODO: This is some random shit that I can't understand
    //       So, it would be better to research how to better implement this viscous movement
    // if (yIn > 0) {
    //     Vector2 facingDirection = Vector2Rotate(
    //         (Vector2){0, 1}, player->rotation * DEG2RAD
    //     );
    //     player->velocity = Vector2Add(
    //         player->velocity,
    //         Vector2Scale(facingDirection, PLAYER_ACCELERATION * dt)
    //     );
    //     float mag = Vector2Length(player->velocity);
    //
    //     if (mag > PLAYER_SPEED) {
    //         player->velocity = Vector2Scale(player->velocity, PLAYER_SPEED / mag);
    //     }
    // }

    player->pos = Vector2Add(
        player->pos,
        Vector2Scale(player->velocity, dt)
    );
}

void PlayerDraw(Player *player)
{
    DrawPoly(player->pos, 3, 64, player->rotation, WHITE);
}
