#pragma once

#include "pathfinder/execution_parameters.h"
#include "pathfinder/pathfinder_result.h"
#include "pathfinder/position.h"
#include "pathfinder/pathfinder_context.h"

#include "ui_elements_observers.h"

#include <memory>
#include <optional>

enum class Algorithm {
    BFS = 0,
    Dijkstra,
    AStar
};

class AlgorithmManager:
    public IResetButtonObserver,
    public IClearButtonObserver,
    public INextButtonObserver,
    public IPreviousButtonObserver,
    public IForwardButtonObserver,
    public IBackwardButtonObserver
{
private:
    const Algorithm DEFAULT_ALGORITHM = Algorithm::BFS;

    PathfinderContext context;
    std::optional<int> current_step;
    std::optional<PathfinderResult> result;
    std::optional<Algorithm> algorithm_type = Algorithm::BFS;

public:
    bool AlgorithHasBeenExecuted() const {return result.has_value();}
    void SetAlgorithmType(Algorithm algorithm_type) {this->algorithm_type = algorithm_type;}
    void RunAlgorithm(int nr_of_rows_and_cols, Position start_position, Position finish_position, std::vector<Position> obstacle_positions);
    void ResetState();

    int GetTotalNumberOfSteps() const;
    int GetCurrentStep() const;
    bool StepIsIncrementable() const;
    bool StepIsDecrementable() const;
    void IncrementStep();
    void DecrementStep();
    void SetStepToZero();
    void SetStepToLast();

    SetOfPositions GetExploredPositionsAtCurrentStep() const;
    bool PathHasBeenFound() const;
    VectorOfPositions GetPath() const;

    void NotifyResetButton() override;
    void NotifyClearButton() override;
    void NotifyNextButton() override;
    void NotifyPreviousButton() override;
    void NotifyForwardButton() override;
    void NotifyBackwardButton() override;
};