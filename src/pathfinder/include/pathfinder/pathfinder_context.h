#pragma once

#include "pathfinder/pathfinder_algorithm.h"
#include "pathfinder/execution_parameters.h"

#include <memory>
#include <functional>

class PathfinderContext 
{
public:
    void SetAlgorithm(std::function<std::unique_ptr<PathfinderAlgorithm>()> algorithm_factory);
    PathfinderResult ExecuteAlgorithm(ExecutionParameters parameters) const;
    std::unique_ptr<PathfinderAlgorithm> GetAlgorithmInstance() const;

private:
    std::function<std::unique_ptr<PathfinderAlgorithm>()> algorithm_factory_;

    Grid CreateGrid(ExecutionParameters parameters) const;
};