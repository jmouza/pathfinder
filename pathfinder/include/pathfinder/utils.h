#pragma once

#include "pathfinder/position.h"

#include <vector>

/*
Returns the (at most) 8 surrounding positions on the grid of the given position.
Negative positions are not included.
*/
std::vector<Position> GetSurroundingPositions(Position pos);