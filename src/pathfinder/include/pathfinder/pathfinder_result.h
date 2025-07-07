#pragma once

#include <vector>
#include <unordered_set>

#include "pathfinder/position.h"

using SetOfPositions = std::unordered_set<Position, Position::HashFunction>;
using VectorOfPositions = std::vector<Position>;

struct PathfinderResult 
{
    bool found_path = false;
    std::vector<SetOfPositions> explored_steps; /* At each step, all explored positions. */
    VectorOfPositions path; 
};