#pragma once

#include "pathfinder/grid.h"
#include "pathfinder/result.h"

/*
Abstract class representing a pathfinder algorithm. 
*/
class Algorithm 
{
public:
    virtual ~Algorithm() = default;

    /*
    Execute the pathfinder algorithm on the given `grid`.
    */
    virtual const Result Execute(const Grid grid) const = 0;
};