#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "IconsFontAwesome6.h"

#include "constants.h"

#include <string>
#include <SDL.h>
#include <SDL_opengl.h>

class Renderer
{
private:
    SDL_Window* window;
    SDL_GLContext gl_context;
    const char* glsl_version;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

public:
    int SetUpSDL();
    void SetUpDearImGuiContext() const;
    void SetUpFonts() const;
    bool DelayIfMinimized() const;
    void NewFrame() const;
    void Render() const;
    void CleanUp() const;
    SDL_Window* GetWindow() const;
};