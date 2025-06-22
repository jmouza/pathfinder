#pragma once

#include "pathfinder/pathfinder_algorithm.h"

#include <unordered_set>

class BreadthFirstSearch : public PathfinderAlgorithm
{
public:
    BreadthFirstSearch(Grid grid_): PathfinderAlgorithm(grid_) {};
    const PathfinderResult Execute() override;

private:
    SetOfNodes explored_nodes;
    bool IsNodeExplored(const Node node) const;
};