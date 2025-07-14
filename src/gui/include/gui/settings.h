#pragma once

#include "aliases.h"
#include "ui_elements_observers.h"

#include <vector>

struct Settings:
    public IFinerGridButtonObserver,
    public ICoarserGridButtonObserver
{
    int current_speed;
    size_t cell_sizes_index; /* Index in vector `cell_sizes`*/
    std::vector<int> cell_sizes; /* List of possible cell sizes */

    Settings(std::vector<int> cell_sizes, int current_speed, size_t cell_sizes_index) 
    {
        this->cell_sizes = cell_sizes;
        this->current_speed = current_speed;
        this->cell_sizes_index = cell_sizes_index;
    }

    bool CellSizeIsDecreasable() const {return cell_sizes_index > 0;}
    bool CellSizeIsIncreasable() const {return cell_sizes_index < (cell_sizes.size()-1);}

    void DecreaseCellSize() {if (CellSizeIsDecreasable()) {cell_sizes_index--;}}
    void IncreaseCellSize() {if (CellSizeIsIncreasable()) {cell_sizes_index++;}}

    int GetCurrentCellSize() const {return cell_sizes[cell_sizes_index];}

    void NotifyFinerGridButton() override {
        DecreaseCellSize();
    }

    void NotifyCoarserGridButton() override {
        IncreaseCellSize();
    }
};