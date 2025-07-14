#pragma once

#include "imgui.h"
#include "aliases.h"
#include "settings.h"
#include "IconsFontAwesome6.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <string>

#ifndef FONT_DIR
#define FONT_DIR "./fonts/"
#endif

static const std::string WINDOW_NAME = "PathFinder Visualization";

static const int ACTION_BAR_HEIGHT = 30;
static const int GRID_SIZE = 750;
static const int WINDOW_WIDTH = GRID_SIZE;
static const int WINDOW_HEIGHT = GRID_SIZE + ACTION_BAR_HEIGHT;

static const int MIN_SPEED = 5;
static const int MAX_SPEED = 15;
static const int SLOPE = -111;
static const int Y_INTERCEPT = 1111; 

static const std::vector<int> CELL_SIZES = {25, 50, 75, 125, 150};

static const float SLIDER_WIDTH = 100.0f;
static const float SELECTOR_WIDTH = 175.0f;
static const float ICON_FONT_SIZE = 20.0f;
static const ImVec2 BUTTON_SIZE(40, 20);

static const std::string PAUSE_BUTTON_STRING = ICON_FA_PAUSE;
static const std::string START_BUTTON_STRING = ICON_FA_PLAY;
static const std::string RESUME_BUTTON_STRING = ICON_FA_PLAY;
static const std::string RESET_BUTTON_STRING = ICON_FA_ROTATE;
static const std::string CLEAR_BUTTON_STRING = ICON_FA_TRASH;
static const std::string COARSERGRID_BUTTON_STRING = ICON_FA_MAGNIFYING_GLASS_PLUS;
static const std::string FINERGRID_BUTTON_STRING = ICON_FA_MAGNIFYING_GLASS_MINUS;
static const std::string HELP_BUTTON_STRING = ICON_FA_CIRCLE_QUESTION;

static const std::string PAUSE_BUTTON_TOOLTIP = "Pause";
static const std::string START_BUTTON_TOOLTIP = "Start";
static const std::string RESUME_BUTTON_TOOLTIP = "Resume";
static const std::string RESET_BUTTON_TOOLTIP = "Reset";
static const std::string CLEAR_BUTTON_TOOLTIP = "Clear Grid";
static const std::string COARSERGRID_BUTTON_TOOLTIP = "Coarser Grid";
static const std::string FINERGRID_BUTTON_TOOLTIP = "Finer Grid";
static const std::string HELP_BUTTON_TOOLTIP = "Help";

static const PixelCoordinate START_POS_RECTS(0, ACTION_BAR_HEIGHT); /* Top left position of the top-left rectangle of the grid */

static const ImU32 BLACK = ImColor(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
static const ImU32 WHITE = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
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