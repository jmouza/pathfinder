#pragma once

#include "pathfinder/pathfinder_algorithm.h"

#include <unordered_set>
#include <queue>
#include <utility>

class BreadthFirstSearch : public PathfinderAlgorithm
{
public:
    BreadthFirstSearch(): PathfinderAlgorithm() {};
    const PathfinderResult Execute() override;

private:
    SetOfNodes explored_nodes;
    std::queue<std::pair<Node, VectorOfNodes>> queue; /* node and path to that node */
    bool IsNodeExplored(const Node node) const;
    void HandleNeighbors(Node current_node, VectorOfNodes path_to_current_node);
};