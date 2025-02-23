#include "asteroid.h"

#define MAX_ASTEROIDS 64
#define ASTEROID_RANDOM_ANGLE 30
#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 300
#define ASTEROID_CREATION_DELAY 1.0f

static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1;

static AsteroidSize _asteroidSizes[] = {
    AsteroidSizeSmall,
    AsteroidSizeMedium,
    AsteroidSizeLarge,
};

void AddAsteroid(Vector2 pos, AsteroidSize size, int screenW, int screenH);
Vector2 GetNextAsteroidPosition(int screenW, int screenH);

int UpdateAsteroids(int screenW, int screenH)
{
    float dt = GetFrameTime();
    float time = GetTime();
    int count = 0;

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        Asteroid *a = &_asteroids[i];

        if (a) {
            AsteroidUpdate(a, dt);
        }

        if (a->isActive) count++;
    }

    if (time > _lastAsteroidCreationTime + ASTEROID_CREATION_DELAY) {

        AddAsteroid(
            GetNextAsteroidPosition(screenW, screenH),
            _asteroidSizes[GetRandomValue(0, 2)],
            screenW,
            screenH
        );

        _lastAsteroidCreationTime = time;
    }

    return count;
}

void DrawAsteroids()
{

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        Asteroid *a = &_asteroids[i];

        if (a) {
            AsteroidDraw(a);
        }
    }
}

void AddAsteroid(Vector2 pos, AsteroidSize size, int screenW, int screenH)
{
    bool created = false;
    const Vector2 screenCenter = { screenW / 2.0, screenH / 2.0};
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

Vector2 GetNextAsteroidPosition(int screenW, int screenH)
{
    const int padding = 128;
    Vector2 result = {-padding, -padding};

    if (GetRandomValue(0, 1)) {
        if (GetRandomValue(0, 1)) {
            result.y = screenW + padding;
        }

        result.x = GetRandomValue(-padding, screenW + padding);
    } else {
        if (GetRandomValue(0, 1)) {
            result.x = screenH + padding;
        }

        result.y = GetRandomValue(-padding, screenH + padding);
    }

    return result;
}
