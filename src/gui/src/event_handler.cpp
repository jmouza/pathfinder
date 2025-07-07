#include "gui/event_handler.h"

bool EventHandler::WindowClosedEventOccured(SDL_Window* window) const {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
            return false;
        }
    }

    return true;
}

std::optional<MouseClickTypeAndPosition> EventHandler::GetMouseEvent() const {
    MouseClickType mouse_click_type;

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        if (ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift)) {
            mouse_click_type = MouseClickType::ShiftLeftClick;
        }
        else if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl)) {
            mouse_click_type = MouseClickType::CtrlLeftClick;
        }
        else {
            mouse_click_type = MouseClickType::LeftClick;
        }
    }
    else if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
        mouse_click_type = MouseClickType::RightClick;
    }
    else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        mouse_click_type = MouseClickType::MouseReleased;
    }
    else {
        return {};
    }

    return std::optional<MouseClickTypeAndPosition>{std::make_pair(mouse_click_type, ImGui::GetMousePos())};
}