#include <stdlib.h>
#include "debug.h"

bool isDebug(void *state)
{
    return state != NULL;
}

bool showAsteroidCount(void *state)
{
    DebugState *ds = (DebugState *)state;

    if (ds && state != NULL) {
        return ds->showAsteroidCount;
    }

    return false;
}

void toggleAsteroidCount(void *state)
{
    DebugState *ds = (DebugState *)state;

    if (ds && state != NULL) {
        ds->showAsteroidCount = !ds->showAsteroidCount;
    }
}
