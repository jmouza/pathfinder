#pragma once

#include "imgui.h"
#include "mouse_click_type.h"

#include <chrono>
#include <utility>

using PixelCoordinate = ImVec2;
using CellCoordinate = ImVec2;
using MouseClickTypeAndPosition = std::pair<MouseClickType, PixelCoordinate>;

using TimePoint = std::chrono::_V2::system_clock::time_point;
// using TimePoint = std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::_V2::system_clock::duration>;