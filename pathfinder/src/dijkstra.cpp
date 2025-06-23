#include <queue>
#include <vector>
#include <utility>

#include "pathfinder/dijkstra.h"

const PathfinderResult Dijkstra::Execute(Grid grid) {
    PathfinderResult result;

    return result;
}

bool Dijkstra::IsNodeExplored(const Node node) const {
    return (explored_nodes.count(node) != 0);
}