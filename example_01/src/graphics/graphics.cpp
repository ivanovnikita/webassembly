#include <raylib.h>

#include <emscripten/emscripten.h>

extern "C"
{
    Camera CAMERA;
    constexpr int MAX_COLUMNS = 20;
    float HEIGHTS[MAX_COLUMNS];
    Vector3 POSITIONS[MAX_COLUMNS];
    Color COLORS[MAX_COLUMNS];

    void update_draw_frame()
    {
        UpdateCamera(&CAMERA);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(CAMERA);

                DrawPlane(Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 32.0f, 32.0f }, LIGHTGRAY);
                DrawCube(Vector3{ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);
                DrawCube(Vector3{ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);
                DrawCube(Vector3{ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);

                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(POSITIONS[i], 2.0f, HEIGHTS[i], 2.0f, COLORS[i]);
                    DrawCubeWires(POSITIONS[i], 2.0f, HEIGHTS[i], 2.0f, MAROON);
                }

            EndMode3D();

            DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 220, 70, BLUE);

            DrawText("First person camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);

        EndDrawing();
    }

    int main()
    {
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

        CAMERA.position = Vector3{ 4.0f, 2.0f, 4.0f };
        CAMERA.target = Vector3{ 0.0f, 1.8f, 0.0f };
        CAMERA.up = Vector3{ 0.0f, 1.0f, 0.0f };
        CAMERA.fovy = 60.0f;
        CAMERA.projection = CAMERA_PERSPECTIVE;

        for (int i = 0; i < MAX_COLUMNS; i++)
        {
            HEIGHTS[i] = static_cast<float>(GetRandomValue(1, 12));
            POSITIONS[i] = Vector3
            {
                static_cast<float>(GetRandomValue(-15, 15)),
                HEIGHTS[i]/2.0f,
                static_cast<float>(GetRandomValue(-15, 15))
            };
            COLORS[i] = Color
            {
                static_cast<unsigned char>(GetRandomValue(20, 255)),
                static_cast<unsigned char>(GetRandomValue(10, 55)),
                30,
                255
            };
        }

        SetCameraMode(CAMERA, CAMERA_FIRST_PERSON);

        emscripten_set_main_loop(update_draw_frame, 0, 1);

        CloseWindow();

        return 0;
    }
}
