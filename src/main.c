#define DEBUG

#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include "asteroid.h"
#include "debug.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const Vector2 screenCenter = { SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};

#define NEARBLACK CLITERAL(Color){ 15, 15, 15, 255 }
#define ASTEROID_RANDOM_ANGLE 30
#define MAX_ASTEROIDS 64
#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 300
#define ASTEROID_CREATION_DELAY 1.0f

static AsteroidSize _asteroidSizes[] = {
    AsteroidSizeSmall,
    AsteroidSizeMedium,
    AsteroidSizeLarge,
};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1;

#ifdef DEBUG
static DebugState debugState = (DebugState){
    .showAsteroidCount = false,
};
#else
static void *debugState = NULL;
#endif

void DrawDebugInfo();
void UpdateDrawFrame();
void AddAsteroid(Vector2 pos, AsteroidSize size);
Vector2 GetNextAsteroidPosition();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroider");

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{
    float dt = GetFrameTime();
    float time = GetTime();

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        Asteroid *a = &_asteroids[i];

        if (a) {
            AsteroidUpdate(a, dt);
        }
    }

    if (time > _lastAsteroidCreationTime + ASTEROID_CREATION_DELAY) {

        AddAsteroid(
            GetNextAsteroidPosition(),
            _asteroidSizes[GetRandomValue(0, 2)]
        );

        _lastAsteroidCreationTime = time;
    }

    BeginDrawing();

    ClearBackground(NEARBLACK);

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        Asteroid *a = &_asteroids[i];

        if (a) {
            AsteroidDraw(a);
        }
    }

    DrawDebugInfo();

    EndDrawing();
}

void DrawDebugInfo()
{
    if (!isDebug(&debugState)) {
        return;
    }

    Rectangle r = { 10, SCREEN_HEIGHT - 100, 180, 80 };

    if (GuiButton(r, "Show asteroid count")) {
        toggleAsteroidCount(&debugState);
    }

    if (showAsteroidCount(&debugState)) {
        int count = 0;

        for (int i = 0; i < MAX_ASTEROIDS; i++) {
            if (_asteroids[i].isActive) count++;
        }

        DrawText(TextFormat("ASTEROIDS: %d", count), 20, 20, 32, WHITE);
    }
}

void AddAsteroid(Vector2 pos, AsteroidSize size)
{
    bool created = false;
    Vector2 velocity = Vector2Subtract(screenCenter, pos);
    velocity = Vector2Scale(
        Vector2Normalize(velocity),
        GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX)
    );
    velocity = Vector2Rotate(
        velocity,
        GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE) * DEG2RAD
    );

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (_asteroids[i].isActive) continue;

        _asteroids[i] = CreateAsteroid(pos, velocity, size);
        created = true;
        break;
    }

    if (!created) {
        TraceLog(LOG_ERROR, "Failed to create an asteroid, because there was no inactive spots in the array!");
    }
}

Vector2 GetNextAsteroidPosition()
{
    const int padding = 128;
    Vector2 result = {-padding, -padding};

    if (GetRandomValue(0, 1)) {
        if (GetRandomValue(0, 1)) {
            result.y = SCREEN_WIDTH + padding;
        }

        result.x = GetRandomValue(-padding, SCREEN_WIDTH + padding);
    } else {
        if (GetRandomValue(0, 1)) {
            result.x = SCREEN_HEIGHT + padding;
        }

        result.y = GetRandomValue(-padding, SCREEN_HEIGHT + padding);
    }

    return result;
}
