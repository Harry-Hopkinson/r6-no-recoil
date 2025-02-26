#include "raylib.h"
#include "App.hpp"

#include "../include/RecoilPresets.hpp"

App::App()
{
    InitWindow(screenWidth, screenHeight, "R6 No Recoil");
    SetTargetFPS(60);

    isActive = EnableRC;
}

App::~App()
{
    CloseWindow();
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isActive)
            {
                for (int i = 0; i < 5; i++)
                {
                    Vector2 mousePos = GetMousePosition();
                    SetMousePosition(mousePos.x + Recoil.Horizontal, mousePos.y + Recoil.Vertical);
                    WaitTime(0.007);
                }
            }
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);
            DrawText("Recoil Control", 120, 20, 20, RAYWHITE);
            DrawText("Enable: ", 50, 80, 20, RAYWHITE);
            DrawText(isActive ? "ON" : "OFF", 130, 80, 20, isActive ? GREEN : RED);
            DrawText("Mode:", 50, 130, 20, RAYWHITE);
            DrawText(Modes[selectedMode], 120, 130, 20, YELLOW);

            if (IsKeyPressed(KEY_ENTER))
            {
                isActive = !isActive;
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                selectedMode = (selectedMode + 1) % 4;
                RecoilControlMode = Modes[selectedMode];
                Recoil = RecoilPresets[RecoilControlMode];
            }
            if (IsKeyPressed(KEY_UP))
            {
                selectedMode = (selectedMode - 1 + 4) % 4;
                RecoilControlMode = Modes[selectedMode];
                Recoil = RecoilPresets[RecoilControlMode];
            }

            DrawText("[ENTER] Toggle On/Off", 50, 200, 15, LIGHTGRAY);
            DrawText("[UP/DOWN] Change Mode", 50, 230, 15, LIGHTGRAY);
        EndDrawing();
    }
}
