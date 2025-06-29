#pragma once

#include "pathfinder/grid.h"
#include "pathfinder/pathfinder_result.h"

#include <optional>

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

protected:
    std::optional<Grid> grid;
    bool IsObstacle(const Node node) const {return node.IsObstacle();}
};