#include <vector>

#include "pathfinder/node.h"

class Step 
{
    std::vector<Node> explored_nodes;
    std::vector<Node> path_nodes;
};