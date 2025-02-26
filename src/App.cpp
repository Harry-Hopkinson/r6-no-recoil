#include "raylib.h"
#include "App.hpp"

App::App()
{
    const int screenWidth = 1400;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "R6 No Recoil");
    InitAudioDevice();
}

App::~App()
{
    CloseAudioDevice();
    CloseWindow();
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Congrats! You created your first window!", 190, 200, 20, RAYWHITE);
        EndDrawing();
    }
}
