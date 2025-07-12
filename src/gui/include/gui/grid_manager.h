#pragma once

#include <optional>
#include <unordered_map>

#include "pathfinder/position.h"
#include "pathfinder/pathfinder_result.h"

#include "ui_elements_observers.h"
#include "aliases.h"
#include "constants.h"

enum class CellType {
    Default,
    Obstacle,
    Start,
    Finish,
    Path,
    Discovered
};

struct Cell {
    Position cell_coordinate;
    enum CellType cell_type;
    
    Cell(int x, int y, CellType cell_type): cell_coordinate(x, y) {
        this->cell_type = cell_type;
    }
    
    Cell(int x, int y): cell_coordinate(x, y) {
        this->cell_type = CellType::Default;
    }

    void SetCellTypeOrFallBack(CellType target, CellType fall_back) {
        cell_type = (cell_type != target) ? target : fall_back;
    }

    void SetCellType(CellType _cell_type) {
        cell_type = _cell_type;
    }

    struct HashFunction
    {
        size_t operator()(const Cell& cell) const
        {
            Position::HashFunction hasher;
            return hasher(cell.cell_coordinate);
        }
    };
};

class GridManager:
    public IResetButtonObserver,
    public IClearButtonObserver
{
private:

    const std::unordered_map<CellType, ImU32> CELL_TYPE_TO_COLOR = {
        {CellType::Default, CELL_DEFAULT_COLOR},
        {CellType::Start, CELL_START_COLOR},
        {CellType::Finish, CELL_FINISH_COLOR},
        {CellType::Obstacle, CELL_OBSTACLE_COLOR},
        {CellType::Path, CELL_PATH_COLOR},
        {CellType::Discovered, CELL_VISITED_COLOR}
    };

    using VectorOfCells = std::vector<Cell>;
    VectorOfCells cells;
    Cell* last_selected = nullptr;
    Cell* start_cell = nullptr;
    Cell* finish_cell = nullptr;

    std::optional<int> nr_of_rows_and_cols;
    std::optional<int> size_of_cell_side;

    PixelCoordinate CellCoordinateToPixelCoordinate(Position cell_coordinate, int size_of_cell_side, int x_offset, int y_offset) const;
    Position PixelCoordinateToCellCoordinate(PixelCoordinate pixel_coordinate, int size_of_cell_side, int x_offset, int y_offset) const;
    size_t CellCoordinateToVectorIndex(Position cell_coordinate, size_t nr_columns) const;
    bool CellCoordinateIsOnGrid(Position cell_coordinate) const;
    
    void SetStartCell(Cell &cell);
    void SetFinishCell(Cell &cell);
public:
    void CreateCellsInGrid();
    void UpdateGrid(SetOfPositions explored_positions, VectorOfPositions path_positions);
    void DrawGrid() const;
    void ResetGrid();

    void HandleMouseClick(MouseClickType click_type, PixelCoordinate pixel_coordindate);
    
    void SetNumberOfRowsAndCols(int nr_of_rows_and_cols) {this->nr_of_rows_and_cols = nr_of_rows_and_cols;};
    void SetSizeOfCells(int size_of_cell_side) {this->size_of_cell_side = size_of_cell_side;}

    bool StartPositionSet() const {return start_cell != nullptr;}
    bool FinishPositionSet() const {return finish_cell != nullptr;}
    
    VectorOfPositions GetObstaclesPositions() const;
    Position GetStartPosition() const;
    Position GetFinishPosition() const;

    void NotifyResetButton() override;
    void NotifyClearButton() override;
};