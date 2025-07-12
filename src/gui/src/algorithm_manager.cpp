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
        // context.SetAlgorithm([]()
        //     {return std::make_unique<BreadthFirstSearch>();
        // });
        break;
    default:
        break;
    }

    result = context.ExecuteAlgorithm(parameters);
    current_step = 0;
}

void AlgorithmManager::ResetState() {
    current_step.reset();
    result.reset();
    algorithm_type = DEFAULT_ALGORITHM;
}

int AlgorithmManager::GetTotalNumberOfSteps() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return result->explored_steps.size();
}

int AlgorithmManager::GetCurrentStep() const {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return current_step.value();
}

bool AlgorithmManager::StepIsIncrementable() const {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return current_step < (GetTotalNumberOfSteps() - 1);
}

bool AlgorithmManager::StepIsDecrementable() const {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return current_step > 0;
}

void AlgorithmManager::IncrementStep() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}
    if (!StepIsIncrementable()) {throw std::runtime_error("Last step has been reached already!");}

    current_step.value() += 1;
}

void AlgorithmManager::DecrementStep() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}
    if (!StepIsDecrementable()) {throw std::runtime_error("Already on first step!");}

    current_step.value() -= 1;
}

void AlgorithmManager::SetStepToZero() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    current_step.value() = 0;
}

void AlgorithmManager::SetStepToLast() {
    if (!current_step) {throw std::runtime_error("Algorithm has not been ran yet!");}

    current_step.value() = GetTotalNumberOfSteps()-1;
}

SetOfPositions AlgorithmManager::GetExploredPositionsAtCurrentStep() const {
    if (!result) {throw std::runtime_error("Algorithm has not been ran yet!");}

    return result->explored_steps.at(current_step.value());
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

void AlgorithmManager::NotifyNextButton() {
    IncrementStep();
}

void AlgorithmManager::NotifyPreviousButton() {
    DecrementStep();
}

void AlgorithmManager::NotifyForwardButton() {
    SetStepToLast();
}

void AlgorithmManager::NotifyBackwardButton() {
    SetStepToZero();
}