#define WIN32_LEAN_AND_MEAN
#include <thread>
#include <chrono>

#include "../include/RecoilPresets.hpp"
#include "../include/UI.hpp"

// Function to center text
void DrawCenteredText(HDC hdc, LPCSTR text, int yOffset, int windowWidth)
{
    SIZE textSize;
    GetTextExtentPoint32(hdc, text, strlen(text), &textSize);
    int textX = (windowWidth - textSize.cx) / 2;
    TextOut(hdc, textX, yOffset, text, strlen(text));
}

// Window Procedure for handling events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            Running = false;
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) // Toggle Recoil Button
            {
                EnableRC = !EnableRC;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            else if (LOWORD(wParam) == 2) // Change Mode Button
            {
                SelectedMode = (SelectedMode + 1) % 4;
                CurrentRecoil = RecoilPresets[SelectedMode];
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;

        case WM_CREATE:
        {
            int centerX = (WINDOW_WIDTH - 150) / 2; // Center buttons horizontally
            buttons.emplace_back(hwnd, centerX, 200, 150, 40, "Toggle Recoil", 1);
            buttons.emplace_back(hwnd, centerX, 250, 150, 40, "Change Mode", 2);
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Get window size
            RECT rect;
            GetClientRect(hwnd, &rect);

            // Set background to black
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);

            // Set text color to white
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);

            // Draw centered text
            DrawCenteredText(hdc, "Recoil Control", 50, rect.right);
            DrawCenteredText(hdc, "Enable:", 100, rect.right);
            DrawCenteredText(hdc, EnableRC ? "ON" : "OFF", 120, rect.right);
            DrawCenteredText(hdc, "Mode:", 150, rect.right);
            DrawCenteredText(hdc, Modes[SelectedMode], 170, rect.right);

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
    RegisterClass(&wc);

    // Create Window
    HWND hwnd = CreateWindowEx(0, "NoRecoilWindow", "R6 No Recoil", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);
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
