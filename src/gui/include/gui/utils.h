#pragma once

#include "imgui.h"
#include "aliases.h"

#include <cmath>

CellCoordinate PixelCoordinateToCellCoordinate(PixelCoordinate pixel_coordinate, float cell_width, float x_offset = 0, float y_offset = 0);
size_t CellCoordinateToVectorIndex(CellCoordinate cell_coordinate, size_t nr_columns);
int LinearEquation(int x, int slope, int y_intercept);