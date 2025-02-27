#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <windows.h>
#include <string>

class Button
{
public:
    Button(HWND parent, int x, int y, int width, int height, const std::string& text, int id)
        : hwndButton(nullptr), id(id)
    {
        hwndButton = CreateWindow(
            "BUTTON", text.c_str(),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            x, y, width, height,
            parent, (HMENU)(uintptr_t)id, GetModuleHandle(NULL), NULL);
    }

private:
    HWND hwndButton;
    int id;
};

#endif
