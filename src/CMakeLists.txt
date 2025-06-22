add_executable(pathfinder_vis main.cpp)

if(MSVC)
  target_compile_options(pathfinder_vis PRIVATE /W4 /WX)
else()
  target_compile_options(pathfinder_vis PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(pathfinder_vis PRIVATE pathfinder)