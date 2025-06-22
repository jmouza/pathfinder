#pragma once

#include <vector>
#include <unordered_set>

#include "pathfinder/node.h"

using SetOfNodes = std::unordered_set<Node, Node::HashFunction>;

struct PathfinderResult 
{
    bool found_path = false;
    std::vector<SetOfNodes> explored_steps; /* At each step, all explored nodes. */
    std::vector<Node> path; 
};