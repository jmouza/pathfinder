add_library(
    gui STATIC 
    src/algorithm_manager.cpp
    src/application.cpp 
    src/event_handler.cpp 
    src/grid_manager.cpp 
    src/renderer.cpp 
    src/state_manager.cpp
    src/ui_elements_manager.cpp 
    src/utils.cpp
)

target_include_directories(gui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${CMAKE_SOURCE_DIR}/src/pathfinder/include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(gui PRIVATE 
    imgui
    ${SDL2_LIBRARIES}
)

target_compile_definitions(gui PUBLIC 
    FONT_DIR="${CMAKE_BINARY_DIR}/fonts/"
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/fonts
     DESTINATION ${CMAKE_BINARY_DIR})