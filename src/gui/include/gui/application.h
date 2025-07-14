#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "settings.h"
#include "timer.h"
#include "ui_elements_observers.h"

#include "renderer.h"
#include "event_handler.h"
#include "ui_elements_manager.h"
#include "grid_manager.h"
#include "algorithm_manager.h"
#include "state_manager.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

class Application:
    public std::enable_shared_from_this<Application>,
    public IStartButtonObserver,
    public IFinerGridButtonObserver,
    public ICoarserGridButtonObserver
{    
private:
    UIElementsManager ui_elements_manager;  
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<EventHandler> event_handler;
    std::shared_ptr<GridManager> grid_manager;
    std::shared_ptr<AlgorithmManager> algorithm_manager;
    std::shared_ptr<StateManager> state_manager;
    std::shared_ptr<Settings> settings;

    void UpdateGridWithCurrentAlgorithmState() const;
    void UpdateGridWithCurrentSettings() const;
    
    bool running_loop = true;
    Timer timer;

public:
    Application();
    void InitializeObservers();
    int SetUpUI();
    void RunMainLoop();

    void NotifyStartButton() override;
    void NotifyFinerGridButton() override;
    void NotifyCoarserGridButton() override;
};