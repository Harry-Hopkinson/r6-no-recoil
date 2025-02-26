#include "raylib.h"
#include "App.hpp"

#include "../include/RecoilPresets.hpp"

App::App()
{
    InitWindow(screenWidth, screenHeight, "R6 No Recoil");
    SetTargetFPS(60);
}

App::~App()
{
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
