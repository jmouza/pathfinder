add_library(
    pathfinder STATIC
    src/node.cpp
    src/grid.cpp
    src/breadth_first_search.cpp
)

target_include_directories(pathfinder PUBLIC include)