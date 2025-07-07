#pragma once

#include "imgui.h"
#include "aliases.h"
#include "settings.h"
#include "IconsFontAwesome6.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

#ifndef FONT_DIR
#define FONT_DIR "./fonts/"
#endif

static const int ACTION_BAR_HEIGHT = 30;
static const int GRID_SIZE = 1000;
static const int WINDOW_WIDTH = GRID_SIZE;
static const int WINDOW_HEIGHT = GRID_SIZE + ACTION_BAR_HEIGHT;

static const int MIN_SPEED = 1;
static const int MAX_SPEED = 10;
static const int SLOPE = -111;
static const int Y_INTERCEPT = 1111; 

static const std::vector<int> CELL_SIZES = {20, 25, 40, 50, 100, 125};

static const float SLIDER_WIDTH = 100.0f;
static const float SELECTOR_WIDTH = 200.0f;
static const float ICON_FONT_SIZE = 20.0f;
static const ImVec2 BUTTON_SIZE(40, 20);

static const char *PAUSE_BUTTON_STRING = ICON_FA_PAUSE;
static const char *START_BUTTON_STRING = ICON_FA_PLAY;
static const char *RESET_BUTTON_STRING = ICON_FA_ROTATE;
static const char *CLEAR_BUTTON_STRING = ICON_FA_TRASH;
static const char *PREVIOUS_BUTTON_STRING = ICON_FA_ANGLE_LEFT;
static const char *NEXT_BUTTON_STRING = ICON_FA_ANGLE_RIGHT;
static const char *BACKWARD_BUTTON_STRING = ICON_FA_ARROW_LEFT;
static const char *FORWARD_BUTTON_STRING = ICON_FA_ARROW_RIGHT;
static const char *COARSERGRID_BUTTON_STRING = ICON_FA_MAGNIFYING_GLASS_PLUS;
static const char *FINERGRID_BUTTON_STRING = ICON_FA_MAGNIFYING_GLASS_MINUS;
static const char *HELP_BUTTON_STRING = ICON_FA_CIRCLE_QUESTION;

static const PixelCoordinate START_POS_RECTS(0, ACTION_BAR_HEIGHT); /* Top left position of the top-left rectangle of the grid */

// static const char *ALGORITHMS[] = {"Breadth-First Search", "Depth-First Search", "Dijkstra's", "A*"};

static const ImU32 BLACK = ImColor(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
static const ImU32 WHITE = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
// static const ImU32 GRAY = ImColor(ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
static const ImU32 DARKGRAY = ImColor(ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
static const ImU32 GRAY = ImColor(ImVec4(0.95f, 0.95f, 0.95f, 1.0f));
static const ImU32 BLUE = ImColor(ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
static const ImU32 RED = ImColor(ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
static const ImU32 YELLOW = ImColor(ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
static const ImU32 GREEN = ImColor(ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
static const ImU32 BRIGHTBLUE = ImColor(ImVec4(0.1f, 0.5f, 1.0f, 1.0f));
static const ImU32 LIGHTBLUE = ImColor(ImVec4(0.7f, 0.9f, 1.0f, 1.0f));

static const ImU32 CELL_BORDER_COLOR = BLACK;
static const ImU32 CELL_DEFAULT_COLOR = GRAY;
static const ImU32 CELL_START_COLOR = GREEN;
static const ImU32 CELL_FINISH_COLOR = RED;
static const ImU32 CELL_OBSTACLE_COLOR = DARKGRAY;
static const ImU32 CELL_PATH_COLOR = BRIGHTBLUE;
static const ImU32 CELL_VISITED_COLOR = LIGHTBLUE;

static const std::unordered_map<CellType, ImU32> CELL_TYPE_TO_COLOR = {
    {CellType::Default, CELL_DEFAULT_COLOR},
    {CellType::Start, CELL_START_COLOR},
    {CellType::Finish, CELL_FINISH_COLOR},
    {CellType::Obstacle, CELL_OBSTACLE_COLOR},
    {CellType::Path, CELL_PATH_COLOR},
    {CellType::Discovered, CELL_VISITED_COLOR}
};

using ACCESS_TABLE_TYPE = std::unordered_map<State, std::unordered_set<const char*>>;
/* For each state, the button (name) that should be enabled. */
static const ACCESS_TABLE_TYPE ACCESS_TABLE = {
    {State::Idle, {START_BUTTON_STRING, RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, FINERGRID_BUTTON_STRING, COARSERGRID_BUTTON_STRING, HELP_BUTTON_STRING}},
    {State::Running, {PAUSE_BUTTON_STRING, RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, HELP_BUTTON_STRING}},
    {State::Paused, {START_BUTTON_STRING, RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, PREVIOUS_BUTTON_STRING, NEXT_BUTTON_STRING, FORWARD_BUTTON_STRING, BACKWARD_BUTTON_STRING, HELP_BUTTON_STRING}},
    {State::Finished, {RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, PREVIOUS_BUTTON_STRING, BACKWARD_BUTTON_STRING, HELP_BUTTON_STRING}}
};

/* For each state, the allowed next state */
static const std::unordered_map<State, std::unordered_set<State>> STATE_TRANSITIONS = {
    {State::Idle, {State::Running}},
    {State::Running, {State::Idle, State::Paused, State::Finished}},
    {State::Paused, {State::Paused, State::Idle, State::Running, State::Finished}}, // stay in pause on next/previous button
    {State::Finished, {State::Idle, State::Paused, State::Running}}
};