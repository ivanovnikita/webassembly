#include <raylib.h>

#include <emscripten/emscripten.h>

extern "C"
{
    void UpdateDrawFrame()
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    int main()
    {
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

        CloseWindow();

        return 0;
    }
}
