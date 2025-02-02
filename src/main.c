#include <raylib.h>
#include "asteroid.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#define NEARBLACK CLITERAL(Color){ 15, 15, 15, 255 }
#define MAX_ASTEROIDS 64

static AsteroidSize _asteroidSizes[] = {
    AsteroidSizeSmall,
    AsteroidSizeMedium,
    AsteroidSizeLarge,
};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};

void UpdateDrawFrame();
void AddAsteroid(Vector2 pos, Vector2 velocity, AsteroidSize size);

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

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        Asteroid *a = &_asteroids[i];

        if (a)
        {
            AsteroidUpdate(a, dt);
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {

        AddAsteroid(
            GetMousePosition(),
            (Vector2){ 200, 0 },
            _asteroidSizes[GetRandomValue(0, 2)]
        );
    }

    BeginDrawing();

    ClearBackground(NEARBLACK);

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        Asteroid *a = &_asteroids[i];

        if (a)
        {
            AsteroidDraw(a);
        }
    }

    EndDrawing();
}

void AddAsteroid(Vector2 pos, Vector2 velocity, AsteroidSize size)
{
    bool created = false;

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (_asteroids[i].isActive) continue;

        _asteroids[i] = CreateAsteroid(pos, velocity, size);
        created = true;
        break;
    }

    if (!created)
    {
        TraceLog(LOG_ERROR, "Failed to create an asteroid, because there was no inactive spots in the array!");
    }
}
