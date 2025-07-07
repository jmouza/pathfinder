#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "utils.h"
#include "constants.h"
#include "settings.h"
#include "timer.h"

#include "renderer.h"
#include "event_handler.h"
#include "ui_elements_manager.h"
#include "grid_manager.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

class Application
{
public:
    Application();
    int SetUpUI();
    void RunMainLoop();
private:
    Renderer renderer;
    EventHandler event_handler;
    std::shared_ptr<Settings> settings = nullptr;
    UIElementsManager ui_elements_manager;
    GridManager grid_manager;
    
    bool running_loop = true;
    Timer timer;
};