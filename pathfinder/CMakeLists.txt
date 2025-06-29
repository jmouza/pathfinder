add_library(
    pathfinder STATIC
    src/node.cpp
    src/grid.cpp
    src/breadth_first_search.cpp
    src/dijkstra.cpp
    src/pathfinder_context.cpp
)

target_include_directories(pathfinder PUBLIC include)