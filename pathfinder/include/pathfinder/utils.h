#pragma once

#include "pathfinder/position.h"

#include <vector>

/*
Returns the 8 surrounding positions on the grid of the given position.
*/
std::vector<Position> GetSurroundingPositions(Position pos);