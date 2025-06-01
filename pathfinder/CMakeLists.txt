add_library(
    pathfinder STATIC
    src/utils.cpp
    src/node.cpp
    src/grid.cpp
)

target_include_directories(pathfinder PUBLIC include)