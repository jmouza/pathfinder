add_library(
    pathfinder STATIC
    src/dfs.cpp
)

target_include_directories(pathfinder PUBLIC include)