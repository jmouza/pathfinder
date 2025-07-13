#include "gui/grid_manager.h"
#include "gui/constants.h"
#include "gui/utils.h"

#include "imgui.h"

#include <stdexcept>

void GridManager::CreateCellsInGrid() {
    if (!nr_of_rows_and_cols) throw std::runtime_error("`nr_of_rows_and_cols` not set, call SetNumberOfRowsAndCols() first.");

    cells.clear();
    for (int y = 0; y < nr_of_rows_and_cols; y++) {
        for (int x = 0; x < nr_of_rows_and_cols; x++) {
            Cell cell(x, y);
            cells.push_back(cell);
        }
    }
}

void GridManager::DrawGrid() const {
    if (!size_of_cell_side) throw std::runtime_error("`nr_of_rows_and_cols` not set, call SetSizeOfCells() first.");

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (auto cell : cells) {
        PixelCoordinate coord_topleft = CellCoordinateToPixelCoordinate(cell.cell_coordinate, *size_of_cell_side, START_POS_RECTS.x, START_POS_RECTS.y);
        PixelCoordinate coord_bottomleft = PixelCoordinate(coord_topleft.x + *size_of_cell_side, coord_topleft.y + *size_of_cell_side);
        draw_list->AddRectFilled(coord_topleft, coord_bottomleft, CELL_TYPE_TO_COLOR.find(cell.cell_type)->second);
        draw_list->AddRect(coord_topleft, coord_bottomleft, CELL_BORDER_COLOR);
    }
}

void GridManager::ResetGrid() {
    for (auto &cell: cells) {
        cell.SetCellType(CellType::Default);
    }
    start_cell = nullptr;
    finish_cell = nullptr;
    last_selected = nullptr;
}

void GridManager::UpdateGrid(SetOfPositions explored_positions, SetOfPositions path_positions) {
    if (!nr_of_rows_and_cols) throw std::runtime_error("`nr_of_rows_and_cols` not set, call SetNumberOfRowsAndCols() first.");

    for (auto position: explored_positions) {
        auto index = CellCoordinateToVectorIndex(position, *nr_of_rows_and_cols);
        cells[index].SetCellType(CellType::Discovered);
    }

    for (auto position: path_positions) {
        auto index = CellCoordinateToVectorIndex(position, *nr_of_rows_and_cols);
        cells[index].SetCellType(CellType::Path);
    }

    if (start_cell) start_cell->SetCellType(CellType::Start);
    if (finish_cell) finish_cell->SetCellType(CellType::Finish);
}

void GridManager::HandleMouseClick(MouseClickType click_type, PixelCoordinate pixel_coordindate) {
    if (!nr_of_rows_and_cols) throw std::runtime_error("`nr_of_rows_and_cols` not set, call SetNumberOfRowsAndCols() first.");
    if (!size_of_cell_side) throw std::runtime_error("`nr_of_rows_and_cols` not set, call SetSizeOfCells() first.");

    if (ImGui::IsAnyItemHovered()) return;

    Position cell_coordinate = PixelCoordinateToCellCoordinate(pixel_coordindate, *size_of_cell_side, START_POS_RECTS.x, START_POS_RECTS.y);

    if (!CellCoordinateIsOnGrid(cell_coordinate)) return;

    Cell &cell = cells[CellCoordinateToVectorIndex(cell_coordinate, *nr_of_rows_and_cols)];

    switch (click_type)
    {
    case MouseClickType::MouseReleased:
        last_selected = nullptr;
        break;
    case MouseClickType::LeftClick:
        if (&cell != last_selected) {
            if (cell.cell_type == CellType::Start) {start_cell = nullptr;}
            else if (cell.cell_type == CellType::Finish) {finish_cell = nullptr;}
            
            cell.SetCellTypeOrFallBack(CellType::Obstacle, CellType::Default);
            last_selected = &cell;
        }
        break;
    case MouseClickType::ShiftLeftClick:
        if (&cell != last_selected) {
            SetStartCell(cell);
        }
        break;
    case MouseClickType::CtrlLeftClick:
        if (&cell != last_selected) {
            SetFinishCell(cell);
        }
        break;
    case MouseClickType::RightClick:
        if (cell.cell_type == CellType::Start) {start_cell = nullptr;}
        else if (cell.cell_type == CellType::Finish) {finish_cell = nullptr;}

        cell.SetCellType(CellType::Default);
        break;
    default:
        break;
    }
}

void GridManager::SetStartCell(Cell &cell) {
    if (start_cell) {
        start_cell->SetCellType(CellType::Default);
    }

    start_cell = &cell;
    cell.SetCellType(CellType::Start);
    last_selected = &cell;

    if (start_cell == finish_cell) {
        finish_cell = nullptr;
    }
}

void GridManager::SetFinishCell(Cell &cell) {
    if (finish_cell) {
        finish_cell->SetCellType(CellType::Default);
    }
    finish_cell = &cell;
    cell.SetCellType(CellType::Finish);
    last_selected = &cell;

    if (finish_cell == start_cell) {
        start_cell = nullptr;
    }
}

PixelCoordinate GridManager::CellCoordinateToPixelCoordinate(Position cell_coordinate, int size_of_cell_side, int x_offset, int y_offset) const {
    return PixelCoordinate(
        cell_coordinate.x * size_of_cell_side + x_offset,
        cell_coordinate.y * size_of_cell_side + y_offset
    );
}

Position GridManager::PixelCoordinateToCellCoordinate(PixelCoordinate pixel_coordinate, int size_of_cell_side, int x_offset, int y_offset) const {
    return Position(
        std::floor((pixel_coordinate.x - x_offset) / size_of_cell_side),
        std::floor((pixel_coordinate.y - y_offset) / size_of_cell_side)
    );
}

size_t GridManager::CellCoordinateToVectorIndex(Position cell_coordinate, size_t nr_columns) const {
    return (cell_coordinate.y * nr_columns) + cell_coordinate.x;
}

bool GridManager::CellCoordinateIsOnGrid(Position cell_coordinate) const {
    if (!nr_of_rows_and_cols) throw std::runtime_error("`nr_of_rows_and_cols` not set, call SetNumberOfRowsAndCols() first.");
    return (cell_coordinate.x >= 0 || cell_coordinate.x < nr_of_rows_and_cols || cell_coordinate.y >= 0 || cell_coordinate.y < nr_of_rows_and_cols);
}

VectorOfPositions GridManager::GetObstaclesPositions() const {
    VectorOfPositions obstacle_positions;

    for (auto cell: cells) {
        if (cell.cell_type == CellType::Obstacle) {
            obstacle_positions.push_back(cell.cell_coordinate);
        }
    }

    return obstacle_positions;
}

Position GridManager::GetStartPosition() const {
    if (!start_cell) throw std::runtime_error("No start position set!");

    return start_cell->cell_coordinate;
}

Position GridManager::GetFinishPosition() const {
    if (!finish_cell) throw std::runtime_error("No finish position set!");

    return finish_cell->cell_coordinate;
}

void GridManager::NotifyResetButton() {
    ResetGrid();
}

void GridManager::NotifyClearButton() {
    ResetGrid();
}

void GridManager::NotifyFinerGridButton() {
    ResetGrid();
}

void GridManager::NotifyCoarserGridButton() {
    ResetGrid();
}