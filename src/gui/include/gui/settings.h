#pragma once

#include "aliases.h"
#include "cell.h"

#include <vector>

enum class Algorithm {
    BFS = 0,
    DFS,
    Dijkstra,
    AStar
};

enum class State {
    Idle,     
    Running,
    Paused,
    Finished
};

struct Settings
{
    enum State state;
    int current_speed;
    size_t cell_sizes_index; /* Index in vector `cell_sizes`*/
    std::vector<int> cell_sizes;
    Cell *start_cell = nullptr;
    Cell *finish_cell = nullptr;
    size_t current_step = 0; /* Current step in the algorithm. */

    Settings(State state, std::vector<int> cell_sizes, int current_speed, size_t cell_sizes_index) {
        this->state = state;
        this->cell_sizes = cell_sizes;
        this->current_speed = current_speed;
        this->cell_sizes_index = cell_sizes_index;
    }

    bool CellSizeIsDecreasable() const {return cell_sizes_index > 0;}
    bool CellSizeIsIncreasable() const {return cell_sizes_index < (cell_sizes.size()-1);}

    void DecreaseCellSize() {if (CellSizeIsDecreasable()) {cell_sizes_index--;}}
    void IncreaseCellSize() {if (CellSizeIsIncreasable()) {cell_sizes_index++;}}

    int GetCurrentCellSize() const {return cell_sizes[cell_sizes_index];}

    void SetDefaultSettings(State state, std::vector<int> cell_sizes, int current_speed, size_t cell_sizes_index) {
        this->state = state;
        this->cell_sizes = cell_sizes;
        this->current_speed = current_speed;
        this->cell_sizes_index = cell_sizes_index;

        start_cell = nullptr;
        finish_cell = nullptr;
        current_step = 0;
    }
};