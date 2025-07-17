#include "pathfinder/pathfinder_context.h"

#include <utility>
#include <stdexcept>

void PathfinderContext::SetAlgorithm(std::unique_ptr<PathfinderAlgorithm> &&algorithm) {
    algorithm_ = std::move(algorithm);
}

PathfinderResult PathfinderContext::ExecuteAlgorithm(ExecutionParameters parameters) const {
    if (!algorithm_) {
        throw std::runtime_error("Algorithm not set!");
    }

    Grid grid = CreateGrid(parameters);

    algorithm_->SetGrid(grid);

    PathfinderResult result = algorithm_->Execute();

    algorithm_->ClearState();

    return result;
}

Grid PathfinderContext::CreateGrid(ExecutionParameters parameters) const {
    Grid grid(parameters.nr_of_columns, parameters.nr_of_rows);
    grid.SetStartNode(parameters.start_node_position);
    grid.SetFinishNode(parameters.finish_node_position);
    
    for (auto position: parameters.obstacle_positions) {
        grid.SetObstacleNode(position);
    }

    return grid;
}

const char* PathfinderContext::GetAlgorithmInstanceName() const {
    if (!algorithm_) {
        throw std::runtime_error("Algorithm not set!");
    }

    return typeid(*algorithm_).name();
}