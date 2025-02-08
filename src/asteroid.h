#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

#define ASTEROID_ROT_SPEED_MIN 5
#define ASTEROID_ROT_SPEED_MAX 240

#define ASTEROID_LIFE 10.0

typedef enum AsteroidSize
{
    AsteroidSizeSmall = 1,
    AsteroidSizeMedium = 2,
    AsteroidSizeLarge = 4,
} AsteroidSize;

typedef struct Asteroid
{
    bool isActive;
    Vector2 pos;
    Vector2 velocity;
    AsteroidSize size;
    float rotation;
    float rotationSpeed;

    float creationTime;
} Asteroid;

Asteroid CreateAsteroid(Vector2 pos, Vector2 velocity, AsteroidSize size);

void AsteroidUpdate(Asteroid *asteroid, float dt);
void AsteroidDraw(Asteroid *asteroid);

#endif
