#pragma once

#include "aliases.h"
#include "ui_elements_observers.h"

#include <vector>

struct Settings:
    public IResetButtonObserver,
    public IFinerGridButtonObserver,
    public ICoarserGridButtonObserver
{
    int current_speed;
    size_t cell_sizes_index; /* Index in vector `cell_sizes`*/
    std::vector<int> cell_sizes; /* List of possible cell sizes */

    const std::vector<int> default_cell_sizes;
    const int default_speed;
    const size_t default_cell_sizes_index;

    Settings(std::vector<int> cell_sizes, int current_speed, size_t cell_sizes_index): 
        default_cell_sizes(cell_sizes), default_speed(current_speed), default_cell_sizes_index(cell_sizes_index) 
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

    void SetDefaultSettings() {
        this->cell_sizes = default_cell_sizes;
        this->current_speed = default_speed;
        this->cell_sizes_index = default_cell_sizes_index;
    }

    void NotifyResetButton() override {
        SetDefaultSettings();
    }

    void NotifyFinerGridButton() override {
        DecreaseCellSize();
    }

    void NotifyCoarserGridButton() override {
        IncreaseCellSize();
    }
};