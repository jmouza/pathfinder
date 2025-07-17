add_library(
    pathfinder STATIC
    src/astar.cpp
    src/breadth_first_search.cpp
    src/dijkstra.cpp
    src/grid.cpp
    src/node.cpp
    src/pathfinder_context.cpp
)

target_include_directories(pathfinder PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)