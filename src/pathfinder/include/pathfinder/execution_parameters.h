#pragma once

#include "pathfinder/position.h"

#include <vector>

struct ExecutionParameters
{
    int nr_of_columns;
    int nr_of_rows;
    Position start_node_position;
    Position finish_node_position;
    std::vector<Position> obstacle_positions;
};