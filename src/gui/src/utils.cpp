#include "gui/utils.h"

CellCoordinate PixelCoordinateToCellCoordinate(PixelCoordinate pixel_coordinate, float cell_width, float x_offset, float y_offset) {
    return ImVec2(
        std::floor((pixel_coordinate.x - x_offset) / cell_width),
        std::floor((pixel_coordinate.y - y_offset) / cell_width)
    );
}

size_t CellCoordinateToVectorIndex(CellCoordinate cell_coordinate, size_t nr_columns) {
    return (cell_coordinate.y * nr_columns) + cell_coordinate.x;
}

int LinearEquation(int x, int slope, int y_intercept) {
    return slope*x + y_intercept;
}