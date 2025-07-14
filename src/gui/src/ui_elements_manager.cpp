#include "gui/ui_elements_manager.h"
#include "gui/constants.h"
#include "imgui.h"

void UIElementsManager::CreateUIElements(State current_state, bool start_and_finish_cell_set, bool cell_size_increasable, bool cell_size_decreasable, int* current_speed) {
    if (current_state == State::Running) {
        if (CreateButtonAndButtonPressed(PAUSE_BUTTON_STRING.c_str(), PAUSE_BUTTON_TOOLTIP.c_str(), ButtonShouldBeEnabledInState(PAUSE_BUTTON_STRING.c_str(), current_state))) {
            HandlePauseButton(); 
        }                                      
    } else if (current_state == State::Paused) {
        if (CreateButtonAndButtonPressed(RESUME_BUTTON_STRING.c_str(), RESUME_BUTTON_TOOLTIP.c_str(), ButtonShouldBeEnabledInState(RESUME_BUTTON_STRING.c_str(), current_state))) {
            HandleResumeButton();
        }
    } else {
        if (CreateButtonAndButtonPressed(START_BUTTON_STRING.c_str(), START_BUTTON_TOOLTIP.c_str(), ButtonShouldBeEnabledInState(START_BUTTON_STRING.c_str(), current_state) && start_and_finish_cell_set)) {
            HandleStartButton();
        }
    }

    if (CreateButtonAndButtonPressed(CLEAR_BUTTON_STRING.c_str(), CLEAR_BUTTON_TOOLTIP.c_str(), ButtonShouldBeEnabledInState(CLEAR_BUTTON_STRING.c_str(), current_state))) 
        HandleClearButton();

    if (CreateButtonAndButtonPressed(RESET_BUTTON_STRING.c_str(), RESET_BUTTON_TOOLTIP.c_str(), ButtonShouldBeEnabledInState(RESET_BUTTON_STRING.c_str(), current_state))) 
        HandleResetButton();

    if (CreateButtonAndButtonPressed(COARSERGRID_BUTTON_STRING.c_str(), COARSERGRID_BUTTON_TOOLTIP .c_str(), ButtonShouldBeEnabledInState(COARSERGRID_BUTTON_STRING.c_str(), current_state) && cell_size_increasable)) 
        HandleCoarserGridButton();

    if (CreateButtonAndButtonPressed(FINERGRID_BUTTON_STRING.c_str(), FINERGRID_BUTTON_TOOLTIP .c_str(), ButtonShouldBeEnabledInState(FINERGRID_BUTTON_STRING.c_str(), current_state) && cell_size_decreasable)) 
        HandleFinerGridButton();

    CreateSlider("##Speed", current_speed, MIN_SPEED, MAX_SPEED, "Speed: %d", "Speed");

    CreateSelector(current_state == State::Idle);


    if (CreateButtonAndButtonPressed(HELP_BUTTON_STRING.c_str(), HELP_BUTTON_TOOLTIP.c_str(), ButtonShouldBeEnabledInState(HELP_BUTTON_STRING.c_str(), current_state)))
        HandleHelpButton();
    
    ShowHelpWindow();
}

bool UIElementsManager::CreateButtonAndButtonPressed(const char* label, const char* tool_tip, bool enabled) const {
    ImGui::SameLine();

    if (!enabled) ImGui::BeginDisabled();
    const bool button =  ImGui::Button(label, BUTTON_SIZE);
    if (!enabled) ImGui::EndDisabled();

    if (ImGui::BeginItemTooltip())
    {
        ImGui::Text("%s", tool_tip);
        ImGui::EndTooltip();
    }

    return button;
}

void UIElementsManager::CreateSlider(const char* label, int *val, int min, int max, const char* format, const char* tool_tip) const {
    ImGui::SameLine();
    ImGui::SetNextItemWidth(SLIDER_WIDTH);

    const bool enabled = true;
    if (!enabled) ImGui::BeginDisabled();
    ImGui::SliderInt(label, val, min, max, format, ImGuiSliderFlags_AlwaysClamp);
    if (!enabled) ImGui::EndDisabled();

    if (ImGui::BeginItemTooltip())
    {
        ImGui::Text("%s", tool_tip);
        ImGui::EndTooltip();
    }
}

void UIElementsManager::CreateSelector(bool enabled) const {
    ImGui::SameLine();
    ImGui::SetNextItemWidth(SELECTOR_WIDTH);

    static int item_selected_idx = 0; 

    if (!enabled) ImGui::BeginDisabled();

    const char* ALGORITHMS[] = {"Breadth-First Search", "Dijkstra's", "A*"}; /* Bad place... */
    if (ImGui::Combo("##Algorithm", &item_selected_idx, ALGORITHMS, IM_ARRAYSIZE(ALGORITHMS)))
    {
        HandleAlgorithmSelector(ALGORITHMS[item_selected_idx]);
    }
    if (!enabled) ImGui::EndDisabled();

    if (ImGui::BeginItemTooltip())
    {
        ImGui::Text("%s", "Algorithm Selection");
        ImGui::EndTooltip();
    }
}

void UIElementsManager::WriteStateText(State current_state, bool is_startable, bool path_found) const {
    ImGui::SameLine();
    switch (current_state)
    {
    case State::Idle:
        if (!is_startable) 
            ImGui::Text("Create a Grid");
        else
            ImGui::Text("Run Algorithm");    
        break;
    case State::Running:
        ImGui::Text("Searching...");
        break;
    case State::Paused:
        ImGui::Text("Paused");
        break;
    case State::Finished:
        if (path_found)
            ImGui::Text("Path Found!");
        else
            ImGui::Text("No Path Found!");    
        break;
    default:
        ImGui::Text(" ");
        break;
    }
}

bool UIElementsManager::ButtonShouldBeEnabledInState(const char* button_string, State current_state) const {
    return BUTTON_ENABLED_STATES_TABLE.at(current_state).count(button_string) != 0;
}

void UIElementsManager::HandleStartButton() {
    for (auto observer: StartButtonObservers) observer->NotifyStartButton();

    /*
    Set state to start
    Execute algorithm
    */
}

void UIElementsManager::HandlePauseButton() {
    for (auto observer: PauseButtonObservers) observer->NotifyPauseButton();

    /*
    Set state to pause
    */
}

void UIElementsManager::HandleResumeButton() {
    for (auto observer: ResumeButtonObservers) observer->NotifyResumeButton();

    /*
    Set state to pause
    */
}

void UIElementsManager::HandleResetButton() {
    for (auto observer: ResetButtonObservers) observer->NotifyResetButton();

    /*
    Set state to idle
    Reset state of the algorithm
    */
}

void UIElementsManager::HandleClearButton() {
    for (auto observer: ClearButtonObservers) observer->NotifyClearButton();

    /*
    Set state to idle
    Reset state of the algorithm
    Reset the grid
    */
}

void UIElementsManager::HandleFinerGridButton() {
    for (auto observer: FinerGridButtonObservers) observer->NotifyFinerGridButton();

    /*
    Decrease cell size in settings
    Notify grid that nr_rows_cols changed
    Recreate the grid
    */
}

void UIElementsManager::HandleCoarserGridButton() {
    for (auto observer: CoarserGridButtonObservers) observer->NotifyCoarserGridButton();

    /*
    Increase cell size in settings
    Notify grid that nr_rows_cols changed
    Recreate the grid
    */
}

void UIElementsManager::HandleHelpButton() const {
    ImGui::OpenPopup("HelpPopUp");
}

void UIElementsManager::ShowHelpWindow() const {
    if (ImGui::BeginPopup("HelpPopUp")) {
        ImGui::SeparatorText("Guide");
        ImGui::BulletText("%s", "<Shift + <left-click> to select start node");
        ImGui::BulletText("%s", "<CTRL> + <left-click> to select finish node");
        ImGui::BulletText("%s", "<Left-click> to select obstacles nodes");
        ImGui::BulletText("%s", "<Right-click> to clear a node");
        ImGui::EndPopup();
    }
}

void UIElementsManager::HandleAlgorithmSelector(const char* selected_algorithm) const {
    for (auto observer: AlgorithmSelectorObservers) observer->NotifyAlgorithmSelector(selected_algorithm);
}