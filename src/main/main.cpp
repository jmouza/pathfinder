#include "gui/application.h"

int main()
{
    Application app;

    if (app.SetUpUI() == -1) {
        return -1;
    }

    app.RunMainLoop();

    return 0;
}