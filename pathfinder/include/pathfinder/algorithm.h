#include "pathfinder/grid.h"
#include "pathfinder/result.h"

/*
Abstract class representing a pathfinder algorithm. 
*/
class Algorithm 
{
public:
    virtual ~Algorithm() = default;
    virtual Result Execute(Grid grid) const = 0;
};