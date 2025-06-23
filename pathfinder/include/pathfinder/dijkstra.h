#pragma once

#include "pathfinder/pathfinder_algorithm.h"

#include <unordered_set>

class Dijkstra : public PathfinderAlgorithm
{
public:
    const PathfinderResult Execute(Grid grid) override;

private:
    SetOfNodes explored_nodes;
    bool IsNodeExplored(const Node node) const;
};