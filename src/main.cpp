#include "App.hpp"

int main()
{
    App* app = new App();
    app->Run();
    delete app;
    return 0;
}
