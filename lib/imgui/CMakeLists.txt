add_library(
    imgui STATIC 
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp 
    backends/imgui_impl_opengl3.cpp 
    backends/imgui_impl_sdl2.cpp 
)

target_include_directories(imgui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/backends
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(imgui PUBLIC
  ${SDL2_LIBRARIES}
)

if(UNIX AND NOT APPLE)
  target_link_libraries(imgui PUBLIC OpenGL::GL)
endif()