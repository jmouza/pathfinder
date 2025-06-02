#include <vector>

#include "pathfinder/step.h"

struct Result 
{
    bool found_path = false;
    std::vector<Step> steps; 
};