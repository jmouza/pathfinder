#pragma once

#include <SDL.h>
#include <optional>
#include <utility>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "mouse_click_type.h"
#include "aliases.h"

class EventHandler
{
public:
    bool WindowClosedEventOccured(SDL_Window* window) const;
    std::optional<MouseClickTypeAndPosition> GetMouseEvent() const;
};