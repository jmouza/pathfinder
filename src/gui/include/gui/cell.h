#pragma once

#include "aliases.h"

enum class CellType {
    Default,
    Obstacle,
    Start,
    Finish,
    Path,
    Discovered
};

struct Cell {
    PixelCoordinate coordinate;
    enum CellType cell_type;
    
    Cell(float x, float y, CellType cell_type) {
        coordinate = ImVec2(x, y);
        this->cell_type = cell_type;
    }

    /*
    Set the `cell_type` to `target` if not already, otherwise to `fall_back`
    */
    void ToggleCellType(CellType target, CellType fall_back) {
        cell_type = (cell_type == target) ? fall_back : target;
    }
};