#pragma once

#include "settings.h"
#include "cell.h"

#include <memory>

class GridManager
{
private:
    std::vector<Cell> cells;
    Cell* last_selected = nullptr;

    void SetStartCell(Cell &cell);
    void SetFinishCell(Cell &cell);
// GetObstaclesPositions
// GetStartPosition
// GetFinishPosition
public:
    std::shared_ptr<Settings> settings = nullptr;

    GridManager(std::shared_ptr<Settings> _settings): settings(_settings) {}
    void CreateGrid();
    void UpdateGrid(bool forward = true);
    void DrawGrid() const;
    void HandleMouseClick(MouseClickType click_type, PixelCoordinate pixel_coordindate);
};