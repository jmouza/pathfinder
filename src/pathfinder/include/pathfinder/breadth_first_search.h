#pragma once

#include "pathfinder/pathfinder_algorithm.h"

#include <unordered_set>
#include <queue>
#include <utility>

using SetOfNodes = std::unordered_set<Node, Node::HashFunction>;

class BreadthFirstSearch : public PathfinderAlgorithm
{
public:
    BreadthFirstSearch(): PathfinderAlgorithm() {};
    const PathfinderResult Execute() override;

private:
    SetOfNodes explored_nodes;
    std::queue<std::pair<Node, VectorOfPositions>> queue; /* node and path to that node */

    void AddExploredPositionsToResultStep();
    bool IsNodeExplored(const Node node) const;
    void HandleNeighbors(Node current_node, VectorOfPositions path_to_current_node);
};