#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>
#include <chrono>

#include "../include/RecoilPresets.hpp"

bool running = true;

// Window Procedure for handling events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            running = false;
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            if (wParam == VK_RETURN) EnableRC = !EnableRC;
            if (wParam == VK_DOWN)
            {
                SelectedMode = (SelectedMode + 1) % 4;
                CurrentRecoil = RecoilPresets[SelectedMode];
            }
            if (wParam == VK_UP)
            {
                SelectedMode = (SelectedMode - 1 + 4) % 4;
                CurrentRecoil = RecoilPresets[SelectedMode];
            }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Function to apply recoil correction
void ApplyRecoil()
{
    while (running)
    {
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) // Right Mouse Button
        {
            if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && EnableRC) // Left Mouse Button
            {
                for (int i = 0; i < 5; i++)
                {
                    POINT mousePos;
                    GetCursorPos(&mousePos);
                    SetCursorPos(mousePos.x + CurrentRecoil.Horizontal, mousePos.y + CurrentRecoil.Vertical);
                    std::this_thread::sleep_for(std::chrono::milliseconds(7));
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register Window Class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "NoRecoilWindow";
    RegisterClass(&wc);

    // Create Window
    HWND hwnd = CreateWindowEx(0, "NoRecoilWindow", "R6 No Recoil", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Start recoil correction thread
    std::thread recoilThread(ApplyRecoil);

    // Message Loop
    MSG msg = {};
    while (running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Draw text using GDI
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);

        TextOut(hdc, 120, 20, "Recoil Control", 14);
        TextOut(hdc, 50, 80, "Enable: ", 8);
        TextOut(hdc, 130, 80, EnableRC ? "ON" : "OFF", EnableRC ? 2 : 3);
        TextOut(hdc, 50, 130, "Mode:", 5);
        TextOut(hdc, 120, 130, Modes[SelectedMode], strlen(Modes[SelectedMode]));
        TextOut(hdc, 50, 200, "[ENTER] Toggle On/Off", 20);
        TextOut(hdc, 50, 230, "[UP/DOWN] Change Mode", 21);

        EndPaint(hwnd, &ps);
        InvalidateRect(hwnd, NULL, TRUE);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    recoilThread.join();
    return 0;
}
