#define DEBUG

#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include "game_asteroids.h"
#include "player.h"
#include "debug.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const Vector2 screenCenter = { SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};

#define NEARBLACK CLITERAL(Color){ 15, 15, 15, 255 }

static Player _player;

#ifdef DEBUG
static DebugState debugState = (DebugState){
    .showAsteroidCount = false,
};
#else
static void *debugState = NULL;
#endif

void DrawDebugInfo(int activeAsteroids);
void UpdateDrawFrame();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroider");
    _player = (Player) {
        .pos = screenCenter,
        .velocity = {0},
        .rotation = 0,
    };

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{

    int activeAsteroids = UpdateAsteroids();
    PlayerUpdate(&_player);

    BeginDrawing();
        ClearBackground(NEARBLACK);

        DrawAsteroids();
        PlayerDraw(&_player);
        DrawDebugInfo(activeAsteroids);
    EndDrawing();
}

void DrawDebugInfo(int activeAsteroids)
{
    if (!isDebug(&debugState)) {
        return;
    }

    Rectangle r = { 10, SCREEN_HEIGHT - 100, 180, 80 };

    if (GuiButton(r, "Show asteroid count")) {
        toggleAsteroidCount(&debugState);
    }

    if (showAsteroidCount(&debugState)) {
        DrawText(TextFormat("ASTEROIDS: %d", activeAsteroids), 20, 20, 32, WHITE);
    }
}

