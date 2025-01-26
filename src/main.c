#include <raylib.h>

int main()
{
    InitWindow(1024, 768, "Asteroider");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);

        DrawRectangle(0, 0, 50, 50, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
