#include "gui/application.h"
#include "gui/constants.h"
#include "gui/utils.h"

Application::Application(): 
    renderer(std::make_shared<Renderer>()),
    event_handler(std::make_shared<EventHandler>()),
    grid_manager(std::make_shared<GridManager>()),
    algorithm_manager(std::make_shared<AlgorithmManager>()),
    state_manager(std::make_shared<StateManager>()),
    settings(std::make_shared<Settings>(CELL_SIZES, (MIN_SPEED+MAX_SPEED)/2, CELL_SIZES.size()/2))
{
    UpdateGridWithCurrentSettings();
}

void Application::InitializeObservers() {
    ui_elements_manager.AttachStartButtonObserver(state_manager);
    ui_elements_manager.AttachStartButtonObserver(shared_from_this());

    ui_elements_manager.AttachPauseButtonObserver(state_manager);

    ui_elements_manager.AttachResetButtonObserver(state_manager);
    ui_elements_manager.AttachResetButtonObserver(grid_manager);
    ui_elements_manager.AttachResetButtonObserver(algorithm_manager);
    ui_elements_manager.AttachResetButtonObserver(settings);

    ui_elements_manager.AttachClearButtonObserver(state_manager);
    ui_elements_manager.AttachClearButtonObserver(grid_manager);
    ui_elements_manager.AttachClearButtonObserver(algorithm_manager);

    ui_elements_manager.AttachNextButtonObserver(algorithm_manager);
    ui_elements_manager.AttachNextButtonObserver(shared_from_this());

    ui_elements_manager.AttachPreviousButtonObserver(algorithm_manager);
    ui_elements_manager.AttachPreviousButtonObserver(shared_from_this());

    ui_elements_manager.AttachForwardButtonObserver(algorithm_manager);
    ui_elements_manager.AttachForwardButtonObserver(shared_from_this());

    ui_elements_manager.AttachBackwardButtonObserver(algorithm_manager);
    ui_elements_manager.AttachBackwardButtonObserver(shared_from_this());
}

int Application::SetUpUI() {
    if (renderer->SetUpSDL() == -1) {
        return -1;
    }

    renderer->SetUpDearImGuiContext();
    renderer->SetUpFonts();

    return 0;
}

void Application::RunMainLoop() {
    ImGuiIO& io = ImGui::GetIO();

    while (running_loop) {
        timer.Tick();

        if (!event_handler->WindowClosedEventOccured(renderer->GetWindow())) {
            running_loop = false;
        }

        if (state_manager->GetCurrentState() == State::Idle) {
            if (auto mouse_event = event_handler->GetMouseEvent(); mouse_event.has_value()) {
                grid_manager->HandleMouseClick(mouse_event->first, mouse_event->second);
            }
        }

        if (renderer->DelayIfMinimized()) continue;

        renderer->NewFrame();

        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        
        ImGui::Begin(WINDOW_NAME.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        ui_elements_manager.CreateUIElements(
            state_manager->GetCurrentState(),
            grid_manager->StartPositionSet() && grid_manager->FinishPositionSet(),
            algorithm_manager->StepIsIncrementable(),
            algorithm_manager->StepIsDecrementable(),
            settings->CellSizeIsIncreasable(),
            settings->CellSizeIsDecreasable(),
            &settings->current_speed
        );

        ui_elements_manager.WriteStateText(
            state_manager->GetCurrentState(),
            algorithm_manager->AlgorithHasBeenExecuted() ? algorithm_manager->GetCurrentStep() : 0,
            algorithm_manager->AlgorithHasBeenExecuted() ? algorithm_manager->GetTotalNumberOfSteps() : 0
        );

        grid_manager->DrawGrid();

        ImGui::End();

        renderer->Render();
        
        if (timer.TimeDurationPassed(LinearEquation(settings->current_speed, SLOPE, Y_INTERCEPT)) && state_manager->GetCurrentState() == State::Running) {
            if (algorithm_manager->StepIsIncrementable()) algorithm_manager->IncrementStep();
            UpdateGridWithCurrentAlgorithmState();
        }
    }

    renderer->CleanUp();
}

void Application::UpdateGridWithCurrentAlgorithmState() const {
    grid_manager->UpdateGrid(algorithm_manager->GetExploredPositionsAtCurrentStep(), algorithm_manager->GetPath());
}

void Application::UpdateGridWithCurrentSettings() const {
    grid_manager->SetNumberOfRowsAndCols(GRID_SIZE/settings->GetCurrentCellSize());
    grid_manager->SetSizeOfCells(settings->GetCurrentCellSize());
    grid_manager->CreateCellsInGrid();
}

void Application::NotifyStartButton() {
    algorithm_manager->RunAlgorithm(
        GRID_SIZE/settings->GetCurrentCellSize(),
        grid_manager->GetStartPosition(),
        grid_manager->GetFinishPosition(),
        grid_manager->GetObstaclesPositions()
    );
}

void Application::NotifyNextButton() {
    UpdateGridWithCurrentAlgorithmState();
}

void Application::NotifyPreviousButton() {
    UpdateGridWithCurrentAlgorithmState();
}

void Application::NotifyForwardButton() {
    UpdateGridWithCurrentAlgorithmState();
}

void Application::NotifyBackwardButton() {
    UpdateGridWithCurrentAlgorithmState();
}

void Application::NotifyFinerGridButton() {
    UpdateGridWithCurrentSettings();
}

void Application::NotifyCoarserGridButton() {
    UpdateGridWithCurrentSettings();
}