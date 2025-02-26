#include "raylib.h"
#include "App.hpp"

App::App()
{
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
            ClearBackground(DARKGRAY);
        EndDrawing();
    }
}
