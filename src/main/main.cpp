#include "gui/application.h"

int main()
{
    std::shared_ptr<Application> app = std::make_shared<Application>();

    app->InitializeObservers();

    if (app->SetUpUI() == -1) {
        return -1;
    }

    app->RunMainLoop();

    return 0;
}