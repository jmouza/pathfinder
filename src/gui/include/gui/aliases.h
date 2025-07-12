#pragma once

#include "imgui.h"
#include "mouse_click_type.h"

#include <chrono>
#include <utility>

using PixelCoordinate = ImVec2;
using CellCoordinate = ImVec2;
using MouseClickTypeAndPosition = std::pair<MouseClickType, PixelCoordinate>;

using TimePoint = std::chrono::_V2::system_clock::time_point;