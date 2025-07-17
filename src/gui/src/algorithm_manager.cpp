#include "gui/algorithm_manager.h"
#include "pathfinder/pathfinder_algorithms.h"

#include <stdexcept>
#include <memory>

void AlgorithmManager::RunAlgorithm(int nr_of_rows_and_cols, Position start_position, Position finish_position, std::vector<Position> obstacle_positions) {
    if (result) {throw std::runtime_error("Algorithm has already been ran, call `ResetState` before running again!");}
    if (!algorithm_type) {throw std::runtime_error("No algorithm has been set, call `SetAlgorithmType` before running!");}

    ExecutionParameters parameters{
        nr_of_rows_and_cols, 
        nr_of_rows_and_cols, 
        start_position, 
        finish_position, 
        obstacle_positions
    };

    switch (algorithm_type.value())
    {
    case Algorithm::BFS:
        context.SetAlgorithm([]()
            {return std::make_unique<BreadthFirstSearch>();
        });
        break;
    case Algorithm::Dijkstra:
        context.SetAlgorithm([]()
            {return std::make_unique<Dijkstra>();
        });
        break;
    case Algorithm::AStar:
        context.SetAlgorithm([]()
            {return std::make_unique<AStar>();
        });
        break;
    default:
        break;
    }

    result = context.ExecuteAlgorithm(parameters);
    current_step = 0;
}

void AlgorithmManager::ResetState() {
    current_step.reset();
    explored_positions_index = 0;
    path_positions_index = -1;
    result.reset();
}

int AlgorithmManager::GetTotalNumberOfSteps() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}
        
    return GetTotalNumberOfExplorationSteps() + GetTotalNumberOfPathPositions(); 
}

int AlgorithmManager::GetTotalNumberOfExplorationSteps() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}
    
    return result->explored_steps.size();
}

int AlgorithmManager::GetTotalNumberOfPathPositions() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return PathHasBeenFound() ? result->path.size() : 0;
}

int AlgorithmManager::GetCurrentStep() const {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return current_step.value();
}

bool AlgorithmManager::StepIsIncrementable() const {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return current_step < (GetTotalNumberOfSteps() - 2);
}

bool AlgorithmManager::StepIsDecrementable() const {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return current_step > 0;
}

void AlgorithmManager::IncrementStep() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}
    if (!StepIsIncrementable()) {throw std::runtime_error("Last step has been reached already!");}

    if (explored_positions_index < GetTotalNumberOfExplorationSteps() - 1) {
        explored_positions_index++;
    } else if (path_positions_index < GetTotalNumberOfPathPositions() - 1) {
        path_positions_index++;
    }

    current_step.value() = explored_positions_index + path_positions_index;
}

void AlgorithmManager::DecrementStep() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}
    if (!StepIsDecrementable()) {throw std::runtime_error("Already on first step!");}

    if (path_positions_index >= 0) {
        path_positions_index--;
    } else if (explored_positions_index > 0) {
        explored_positions_index--;
    }

    current_step.value() = explored_positions_index + path_positions_index;
}

void AlgorithmManager::SetStepToZero() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    current_step.value() = 0;
    explored_positions_index = 0;
    path_positions_index = -1;
}

void AlgorithmManager::SetStepToLast() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    explored_positions_index = GetTotalNumberOfExplorationSteps() - 1;
    path_positions_index = GetTotalNumberOfPathPositions() - 1;
    current_step.value() = explored_positions_index + path_positions_index;
}

SetOfPositions AlgorithmManager::GetExploredPositionsAtCurrentStep() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}
    
    return result->explored_steps.at(explored_positions_index);
}

SetOfPositions AlgorithmManager::GetPathPositionsAtCurrentStep() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}

    SetOfPositions positions;
    if (!PathHasBeenFound()) return positions;

    for (int i = 0; i <= path_positions_index; i++) {
        positions.insert(result->path.at(i));
    }

    return positions;
}

bool AlgorithmManager::PathHasBeenFound() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return result->found_path;
}

VectorOfPositions AlgorithmManager::GetPath() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return result->path;
}

void AlgorithmManager::NotifyResetButton() {
    ResetState();
}

void AlgorithmManager::NotifyClearButton() {
    ResetState();
}

void AlgorithmManager::NotifyAlgorithmSelector(std::string selected_algorithm) {
    if (selected_algorithm == "Breadth-First Search") {
        SetAlgorithmType(Algorithm::BFS);
    } else if (selected_algorithm == "Dijkstra's") {
        SetAlgorithmType(Algorithm::Dijkstra);
    } else if (selected_algorithm == "A*") {
        SetAlgorithmType(Algorithm::AStar);
    }
}