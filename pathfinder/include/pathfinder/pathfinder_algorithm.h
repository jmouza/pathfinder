#pragma once

#include "pathfinder/grid.h"
#include "pathfinder/pathfinder_result.h"

class PathfinderAlgorithm 
{
public:
    PathfinderAlgorithm(Grid grid_): grid(grid_) {};
    virtual ~PathfinderAlgorithm() = default;

    /*
    Execute the pathfinder algorithm on the given `grid`.
    */
    virtual const PathfinderResult Execute() = 0;

protected:
    Grid grid;
    bool IsObstacle(const Node node) const {return node.IsObstacle();}
};