#pragma once

#include "pathfinder/position.h"

#include <vector>

/*
Returns the (at most) 8 surrounding positions on the grid of the given position.
Negative positions are not included.
Note: it does return postions that might be outside the grid!
*/
std::vector<Position> GetSurroundingPositions(Position pos, int nr_rows, int nr_cols);