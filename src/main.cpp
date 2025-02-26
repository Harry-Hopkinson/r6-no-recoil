#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>
#include <chrono>

#include "../include/RecoilPresets.hpp"

// Window Procedure for handling events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            Running = false;
            PostQuitMessage(0);
            break;

        case WM_KEYDOWN:
            if (wParam == VK_RETURN) {
                EnableRC = !EnableRC;
                InvalidateRect(hwnd, NULL, TRUE); // Request repaint
            }
            if (wParam == VK_UP)
            {
                SelectedMode = (SelectedMode + 1) % 4;
                CurrentRecoil = RecoilPresets[SelectedMode];
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if (wParam == VK_DOWN)
            {
                SelectedMode = (SelectedMode - 1 + 4) % 4;
                CurrentRecoil = RecoilPresets[SelectedMode];
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Create a black background
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // Black background
            FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);

            // Set text properties
            SetTextColor(hdc, RGB(255, 255, 255)); // White text
            SetBkMode(hdc, TRANSPARENT);

            // Draw text
            TextOut(hdc, 120, 20, "Recoil Control", 14);
            TextOut(hdc, 50, 80, "Enable: ", 8);
            TextOut(hdc, 130, 80, EnableRC ? "ON" : "OFF", EnableRC ? 2 : 3);
            TextOut(hdc, 50, 130, "Mode:", 5);
            TextOut(hdc, 120, 130, Modes[SelectedMode], strlen(Modes[SelectedMode]));
            TextOut(hdc, 50, 200, "[ENTER] Toggle On/Off", 20);
            TextOut(hdc, 50, 230, "[UP/DOWN] Change Mode", 21);

            EndPaint(hwnd, &ps);
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void ApplyRecoil()
{
    while (Running)
    {
        if (EnableRC && (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) // Right Mouse Button (ADS)
        {
            while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // Left Mouse Button (Firing)
            {
                mouse_event(MOUSEEVENTF_MOVE, CurrentRecoil.Horizontal * 2, CurrentRecoil.Vertical * 2, 0, 0);

                std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Background set in WM_PAINT
    RegisterClass(&wc);

    // Create Window
    HWND hwnd = CreateWindowEx(0, "NoRecoilWindow", "R6 No Recoil", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Start recoil correction thread
    std::thread recoilThread(ApplyRecoil);

    // Message Loop
    MSG msg = {};
    while (Running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    recoilThread.join();
    return 0;
}
