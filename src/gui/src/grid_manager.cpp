#include "gui/grid_manager.h"
#include "gui/constants.h"
#include "gui/utils.h"

#include "imgui.h"

void GridManager::CreateGrid() {
    cells.clear();
    for (int dy = 0; dy < GRID_SIZE; dy += settings->GetCurrentCellSize()) {
        for (int dx = 0; dx < GRID_SIZE; dx += settings->GetCurrentCellSize()) {
            Cell c(START_POS_RECTS.x + dx, START_POS_RECTS.y + dy, CellType::Default);
            cells.push_back(c);
        }
    }
}

void GridManager::DrawGrid() const {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (auto cell : cells) {
        draw_list->AddRectFilled(cell.coordinate, ImVec2(cell.coordinate.x + settings->GetCurrentCellSize(), cell.coordinate.y + settings->GetCurrentCellSize()), CELL_TYPE_TO_COLOR.find(cell.cell_type)->second);
        draw_list->AddRect(cell.coordinate, ImVec2(cell.coordinate.x + settings->GetCurrentCellSize(), cell.coordinate.y + settings->GetCurrentCellSize()), CELL_BORDER_COLOR);
    }
}

void GridManager::UpdateGrid(bool forward) {
    /*
    algorithm.results[settings->current_step] should contain all the information at the current state
    */
    if (forward) {settings->current_step++;} else {settings->current_step--;};

    if (settings->current_step >= cells.size()) {
        settings->current_step = cells.size() - 1;
        settings->state = State::Finished;
    } 
    // else if (settings->current_step < 0) {
    //     settings->current_step = 0;
    // } 
    else {
        cells[settings->current_step].ToggleCellType(CellType::Path, CellType::Default);
    }

    /* Based on current algorithm step, update cells of the grid to (DISCOVERED, PATH)*/
}


void GridManager::HandleMouseClick(MouseClickType click_type, PixelCoordinate pixel_coordindate) {
    if (click_type == MouseClickType::MouseReleased) { // TODO: MOVE TO SWITCH????
        last_selected = nullptr;
        return;
    }
    if (settings->state != State::Idle) return;
    if (ImGui::IsAnyItemHovered()) return;

    CellCoordinate cell_coordinate = PixelCoordinateToCellCoordinate(pixel_coordindate, settings->GetCurrentCellSize(), 0.0f, ACTION_BAR_HEIGHT);

    if (cell_coordinate.x < 0 || cell_coordinate.x > (GRID_SIZE/settings->GetCurrentCellSize()) || cell_coordinate.y < 0 || cell_coordinate.y > (GRID_SIZE/settings->GetCurrentCellSize())) return;

    Cell &cell = cells[CellCoordinateToVectorIndex(cell_coordinate, (GRID_SIZE/settings->GetCurrentCellSize()))];

    switch (click_type)
    {
    case MouseClickType::LeftClick:
        if (&cell != last_selected) {
            /* BUG: OVERWRITING A START OR FINISH CELL WITH OBSTACLE DOES NOT REMOVE THE START OR FINISH*/
            cell.ToggleCellType(CellType::Obstacle, CellType::Default);
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
        if (cell.cell_type == CellType::Start) {settings->start_cell = nullptr;}
        else if (cell.cell_type == CellType::Finish) {settings->finish_cell = nullptr;}

        cell.cell_type = CellType::Default;
        break;
    default:
        break;
    }
}

void GridManager::SetStartCell(Cell &cell) {
    if (settings->start_cell != nullptr) {
        settings->start_cell->cell_type = CellType::Default;
    }
    settings->start_cell = &cell;
    cell.cell_type = CellType::Start;
    last_selected = &cell;

    // Override the finish cell to start cell
    if (settings->start_cell == settings->finish_cell) {
        settings->finish_cell = nullptr;
    }
}

void GridManager::SetFinishCell(Cell &cell) {
    if (settings->finish_cell != nullptr) {
        settings->finish_cell->cell_type = CellType::Default;
    }
    settings->finish_cell = &cell;
    cell.cell_type = CellType::Finish;
    last_selected = &cell;

    // Override the start cell to finish cell
    if (settings->finish_cell == settings->start_cell) {
        settings->start_cell = nullptr;
    }
}