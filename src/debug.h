#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdbool.h>

typedef struct DebugState
{
    bool showAsteroidCount;
} DebugState;

bool isDebug(void *state);
void toggleAsteroidCount(void *state);
bool showAsteroidCount(void *state);

#endif
