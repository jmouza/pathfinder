#include "gui/application.h"

Application::Application()
    : settings(std::make_shared<Settings>(State::Idle, CELL_SIZES, (MIN_SPEED+MAX_SPEED)/2, CELL_SIZES.size()/2))
    , ui_elements_manager(settings)
    , grid_manager(settings)
{
    grid_manager.CreateGrid();
}

int Application::SetUpUI() {
    if (renderer.SetUpSDL() == -1) {
        return -1;
    }

    renderer.SetUpDearImGuiContext();
    renderer.SetUpFonts();

    return 0;
}

void Application::RunMainLoop() {
    ImGuiIO& io = ImGui::GetIO();

    while (running_loop) {
        timer.Tick();

        if (!event_handler.WindowClosedEventOccured(renderer.GetWindow())) {
            running_loop = false;
        }

        auto mouse_event = event_handler.GetMouseEvent();
        if (mouse_event.has_value()) {
            grid_manager.HandleMouseClick(mouse_event->first, mouse_event->second);
        }

        if (renderer.DelayIfMinimized()) continue;

        renderer.NewFrame();

        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        
        /* TODO: HARD CODED NAME*/
        ImGui::Begin("window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        ui_elements_manager.CreateUIElements();
        ui_elements_manager.WriteStateText();

        // Set grid state based on algorithm step
        grid_manager.DrawGrid();

        ImGui::End();

        renderer.Render();
        
        if (timer.TimeDurationPassed(LinearEquation(settings->current_speed, SLOPE, Y_INTERCEPT)) && settings->state == State::Running) {
            grid_manager.UpdateGrid();
        }
    }

    renderer.CleanUp();
}