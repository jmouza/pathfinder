add_executable(pathfinder_vis main.cpp)

target_include_directories(pathfinder_vis PRIVATE
    ${CMAKE_SOURCE_DIR}/src/gui/include
    ${CMAKE_SOURCE_DIR}/src/pathfinder/include
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(pathfinder_vis PRIVATE 
    gui
    pathfinder
    imgui 
    ${SDL2_LIBRARIES}
)

if(UNIX AND NOT APPLE)
  target_link_libraries(pathfinder_vis PRIVATE OpenGL::GL)
endif()