#pragma once

#include "pathfinder/pathfinder_algorithm.h"
#include "pathfinder/execution_parameters.h"

#include <memory>

class PathfinderContext 
{
public:
    void SetAlgorithm(std::unique_ptr<PathfinderAlgorithm> &&algorithm);
    PathfinderResult ExecuteAlgorithm(ExecutionParameters parameters) const;
    const char* GetAlgorithmInstanceName() const;

private:
    std::unique_ptr<PathfinderAlgorithm> algorithm_;

    Grid CreateGrid(ExecutionParameters parameters) const;
};