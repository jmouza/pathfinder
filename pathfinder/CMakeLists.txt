add_library(
    pathfinder STATIC
    src/node.cpp
)

target_include_directories(pathfinder PUBLIC include)