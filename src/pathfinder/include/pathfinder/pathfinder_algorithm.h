#pragma once

#include "pathfinder/grid.h"
#include "pathfinder/pathfinder_result.h"

#include <optional>

using SetOfNodes = std::unordered_set<Node, Node::HashFunction>;

class PathfinderAlgorithm 
{
public:
    PathfinderAlgorithm() {};
    virtual ~PathfinderAlgorithm() = default;
    void SetGrid(Grid grid_) {grid = grid_;}
    /*
    Execute the pathfinder algorithm on the given `grid`.
    */
    virtual const PathfinderResult Execute() = 0;
    virtual void ClearState() {
        grid.reset();
        result = PathfinderResult();
    }

protected:
    PathfinderResult result;
    std::optional<Grid> grid;
};