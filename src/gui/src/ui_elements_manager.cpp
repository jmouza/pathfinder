#include "gui/ui_elements_manager.h"
#include "gui/constants.h"
#include "imgui.h"

#include <iostream>

/* TODO: SHOULD NOT BE HERE */
static const char *ALGORITHMS[] = {"Breadth-First Search", "Depth-First Search", "Dijkstra's", "A*"};
static const char *PAUSE_BUTTON_TOOLTIP = "Pause";
static const char *START_BUTTON_TOOLTIP = "Start";
static const char *RESET_BUTTON_TOOLTIP = "Default Settings";
static const char *CLEAR_BUTTON_TOOLTIP = "Clear Grid";
static const char *PREVIOUS_BUTTON_TOOLTIP = "Previous Step";
static const char *NEXT_BUTTON_TOOLTIP = "Next Step";
static const char *BACKWARD_BUTTON_TOOLTIP = "To Start";
static const char *FORWARD_BUTTON_TOOLTIP = "To End";
static const char *COARSERGRID_BUTTON_TOOLTIP = "Coarser Grid";
static const char *FINERGRID_BUTTON_TOOLTIP = "Finer Grid";
static const char *HELP_BUTTON_TOOLTIP = "Help";

void UIElementsManager::CreateUIElements() {
    if (settings->state == State::Running) {
        if (CreateButton(PAUSE_BUTTON_STRING, PAUSE_BUTTON_TOOLTIP, ButtonShouldBeEnabled(PAUSE_BUTTON_STRING)))                                          HandlePauseButton();
    } 
    else {
        if (CreateButton(
                START_BUTTON_STRING, 
                START_BUTTON_TOOLTIP, 
                ButtonShouldBeEnabled(START_BUTTON_STRING) && settings->start_cell != nullptr && settings->finish_cell != nullptr))            HandleStartButton();
    }                                            
    if (CreateButton(CLEAR_BUTTON_STRING, CLEAR_BUTTON_TOOLTIP , ButtonShouldBeEnabled(CLEAR_BUTTON_STRING))) HandleClearButton();
    if (CreateButton(PREVIOUS_BUTTON_STRING, PREVIOUS_BUTTON_TOOLTIP , ButtonShouldBeEnabled(PREVIOUS_BUTTON_STRING) && settings->current_step != 0)) HandlePreviousButton();
    if (CreateButton(NEXT_BUTTON_STRING, NEXT_BUTTON_TOOLTIP , ButtonShouldBeEnabled(NEXT_BUTTON_STRING))) HandleNextButton();
    if (CreateButton(BACKWARD_BUTTON_STRING, BACKWARD_BUTTON_TOOLTIP , ButtonShouldBeEnabled(BACKWARD_BUTTON_STRING) && settings->current_step != 0)) HandleBackwardButton();
    if (CreateButton(FORWARD_BUTTON_STRING, FORWARD_BUTTON_TOOLTIP , ButtonShouldBeEnabled(FORWARD_BUTTON_STRING))) HandleForwardButton();
    if (CreateButton(COARSERGRID_BUTTON_STRING, COARSERGRID_BUTTON_TOOLTIP , ButtonShouldBeEnabled(COARSERGRID_BUTTON_STRING) && settings->CellSizeIsIncreasable())) HandleCoarserGridButton();
    if (CreateButton(FINERGRID_BUTTON_STRING, FINERGRID_BUTTON_TOOLTIP , ButtonShouldBeEnabled(FINERGRID_BUTTON_STRING) && settings->CellSizeIsDecreasable())) HandleFinerGridButton();

    CreateSlider("##Speed", &settings->current_speed, MIN_SPEED, MAX_SPEED, "Speed: %d", "Speed");

    CreateSelector();

    if (CreateButton(RESET_BUTTON_STRING, RESET_BUTTON_TOOLTIP , ButtonShouldBeEnabled(RESET_BUTTON_STRING)))                             HandleResetButton();
    if (CreateButton(HELP_BUTTON_STRING, HELP_BUTTON_TOOLTIP , ButtonShouldBeEnabled(HELP_BUTTON_STRING))) {
        HandleHelpButton();
    }
    ShowHelpWindow();
}

bool UIElementsManager::CreateButton(const char* label, const char* tool_tip, bool enabled) const {
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

void UIElementsManager::CreateSelector() const {
    ImGui::SameLine();
    ImGui::SetNextItemWidth(SELECTOR_WIDTH);

    static int item_selected_idx = 0; 

    const bool enabled = (settings->state == State::Idle);
    if (!enabled) ImGui::BeginDisabled();
    if (ImGui::Combo("##Algorithm", &item_selected_idx, ALGORITHMS, IM_ARRAYSIZE(ALGORITHMS)))
    {
        HandleAlgorithmSelector(static_cast<Algorithm>(item_selected_idx));
    }
    if (!enabled) ImGui::EndDisabled();

    if (ImGui::BeginItemTooltip())
    {
        ImGui::Text("%s", "Algorithm Selection");
        ImGui::EndTooltip();
    }
}

void UIElementsManager::WriteStateText() const {
    ImGui::SameLine();
    switch (settings->state)
    {
    case State::Idle:
        ImGui::Text("Idle");
        break;
    case State::Running:
        ImGui::Text("Running");
        ImGui::SameLine();
        // ImGui::Text("(Step %lu/%lu)", settings->current_step+1, cells.size());
        break;
    case State::Paused:
        ImGui::Text("Paused");
        ImGui::SameLine();
        // ImGui::Text("(Step %lu/%lu)", settings->current_step+1, cells.size());
        break;
    case State::Finished:
        ImGui::Text("Finished");
        ImGui::SameLine();
        // ImGui::Text("(Step %lu/%lu)", settings->current_step+1, cells.size());
        break;
    default:
        ImGui::Text(" ");
        break;
    }
}

bool UIElementsManager::ButtonShouldBeEnabled(const char* button_string) {
    return ((ACCESS_TABLE.find(settings->state)->second.count(button_string)) != 0);
}

void UIElementsManager::HandleStartButton() {
    /* TODO: API Specific Code To Execute algorithm and fetch the result (loading screen? thread?)*/    
    /* Check if start cell and finish cell selected*/
    ChangeState(State::Running);
}

void UIElementsManager::HandlePauseButton() {
    ChangeState(State::Paused);
}

void UIElementsManager::HandleResetButton() {
    /* TODO: API Specific Reset */    
    HandleClearButton();

    // settings = default_settings;
    // CreateGrid();
}

void UIElementsManager::HandleClearButton() {
    // last_selected = nullptr;

    // for (auto &cell : cells) {
    //     cell.cell_type = CellType::Default;
    // }

    settings->start_cell = nullptr;
    settings->finish_cell = nullptr;

    settings->current_step = 0;

    ChangeState(State::Idle);
}

void UIElementsManager::HandleNextButton() {
    ChangeState(State::Paused);
    // UpdateGrid();
}

void UIElementsManager::HandlePreviousButton() {
    ChangeState(State::Paused);
    // UpdateGrid(false);
}

void UIElementsManager::HandleForwardButton() {
    // settings->current_step = cells.size()-1; /* TODO: change this */
    ChangeState(State::Finished);
}

void UIElementsManager::HandleBackwardButton() {
    settings->current_step = 0;
    ChangeState(State::Paused);
}

void UIElementsManager::HandleFinerGridButton() {
    if (settings->CellSizeIsDecreasable()) {
        settings->DecreaseCellSize();
        // CreateGrid();
    }
}

void UIElementsManager::HandleCoarserGridButton() {
    if (settings->CellSizeIsIncreasable()) {
        settings->IncreaseCellSize();
        // CreateGrid();
    }
}

void UIElementsManager::HandleHelpButton() const {
    ImGui::OpenPopup("HelpPopUp");
}

void UIElementsManager::ShowHelpWindow() const {
    if (ImGui::BeginPopup("HelpPopUp")) {
        ImGui::SeparatorText("Guide");
        ImGui::BulletText("%s", "Shift + left-click to select start node");
        ImGui::BulletText("%s", "CTRL + left-click to select finish node");
        ImGui::BulletText("%s", "Left-click to select obstacles nodes");
        ImGui::BulletText("%s", "Right-click to clear a node");
        ImGui::EndPopup();
    }
}

void UIElementsManager::HandleAlgorithmSelector(enum Algorithm selected_algorithm) const {
    /* New API object */
    std::cout << "Algorithm selector used: " << ALGORITHMS[static_cast<int>(selected_algorithm)] << std::endl;
}

void UIElementsManager::ChangeState(State target_state) {
    auto possible_states = STATE_TRANSITIONS.find(settings->state)->second;
    if (possible_states.count(target_state) != 0) {
        settings->state = target_state;
    }
}