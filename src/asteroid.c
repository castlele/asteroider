#include "asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Vector2 pos, Vector2 velocity, AsteroidSize size)
{
    return (Asteroid) {
        .isActive = true,
        .pos = pos,
        .velocity = velocity,
        .size = size,
        .rotation = GetRandomValue(0, 360),
        .rotationSpeed = GetRandomValue(ASTEROID_ROT_SPEED_MIN, ASTEROID_ROT_SPEED_MAX),
    };
}

void AsteroidUpdate(Asteroid *asteroid, float dt)
{
    if (!asteroid->isActive) return;

    asteroid->pos = Vector2Add(
        asteroid->pos,
        Vector2Scale(asteroid->velocity, dt)
    );

    asteroid->rotation += asteroid->rotationSpeed * dt;
}

void AsteroidDraw(Asteroid *asteroid)
{
    DrawPolyLines(asteroid->pos, 3, 16 * (int)asteroid->size, asteroid->rotation, WHITE);
}
