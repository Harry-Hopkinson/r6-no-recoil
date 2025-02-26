#pragma once

class App
{
public:
    App();
    ~App();
    void Run();

private:
    const int screenWidth = 400;
    const int screenHeight = 300;

    int selectedMode = 1;
    bool isActive;
};
