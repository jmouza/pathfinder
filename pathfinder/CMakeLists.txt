add_library(
    pathfinder STATIC
    src/node.cpp
    src/grid.cpp
    src/bfs.cpp
)

target_include_directories(pathfinder PUBLIC include)