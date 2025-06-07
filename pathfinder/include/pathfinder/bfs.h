#pragma once

#include "pathfinder/algorithm.h"

#include <unordered_set>

/*
Breadth-first search algorithm.
*/
class BFS : public Algorithm
{
public:
    const Result Execute(const Grid grid) const override;
    bool IsExplored(const Node node, const std::unordered_set<Node, Node::HashFunction> explored_set) const;
    bool IsObstacle(const Node node) const;
};