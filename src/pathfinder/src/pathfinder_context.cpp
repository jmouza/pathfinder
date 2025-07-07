#include "pathfinder/pathfinder_context.h"

#include <utility>
#include <stdexcept>

void PathfinderContext::SetAlgorithm(std::function<std::unique_ptr<PathfinderAlgorithm>()> algorithm_factory) {
    algorithm_factory_ = std::move(algorithm_factory);
}

PathfinderResult PathfinderContext::ExecuteAlgorithm(ExecutionParameters parameters) const {
    if (!algorithm_factory_) {
        throw std::runtime_error("Algorithm factory function not set!");
    }

    Grid grid = CreateGrid(parameters);

    auto algorithm = algorithm_factory_();
    algorithm->SetGrid(grid);

    PathfinderResult result = algorithm->Execute();

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

std::unique_ptr<PathfinderAlgorithm> PathfinderContext::GetAlgorithmInstance() const {
    if (!algorithm_factory_) {
        throw std::runtime_error("Algorithm factory function not set!");
    }

    return algorithm_factory_();
}