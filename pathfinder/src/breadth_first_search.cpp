#include <queue>
#include <vector>
#include <utility>

#include "pathfinder/breadth_first_search.h"

const PathfinderResult BreadthFirstSearch::Execute(Grid grid) {
    PathfinderResult result;

    std::queue<std::pair<Node, VectorOfNodes>> queue; /* node and path to that node */
    queue.push({grid.GetStartNode(), {}});

    while (!queue.empty()) {
        result.explored_steps.push_back(explored_nodes); 

        auto pair = queue.front();
        queue.pop();

        Node node = pair.first;
        explored_nodes.insert(node); 

        VectorOfNodes path = pair.second;
        path.push_back(node);

        if (node == grid.GetFinishNode()) {
            result.found_path = true;
            result.path = path;
            return result;
        }

        for (const Node adj_node: grid.GetAdjacentNodes(node)) {
            if (!IsNodeExplored(adj_node) && !IsObstacle(adj_node)) {
                queue.push({adj_node, path});
            }
        }
    }

    return result;
}

bool BreadthFirstSearch::IsNodeExplored(const Node node) const {
    return (explored_nodes.count(node) != 0);
}