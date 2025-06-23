#pragma once

#include "pathfinder/grid.h"
#include "pathfinder/pathfinder_result.h"

class PathfinderAlgorithm 
{
public:
    virtual ~PathfinderAlgorithm() = default;

    /*
    Execute the pathfinder algorithm on the given `grid`.
    */
    virtual const PathfinderResult Execute(Grid grid) = 0;

protected:
    bool IsObstacle(const Node node) const {return node.IsObstacle();}
};