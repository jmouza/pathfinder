#include <vector>

#include "pathfinder/breadth_first_search.h"

const PathfinderResult BreadthFirstSearch::Execute() {
    PathfinderResult result;

    Node start_node = grid.GetStartNode();
    Node finish_node = grid.GetFinishNode();

    queue.push({start_node, {}});
    explored_nodes.insert(start_node); 

    while (!queue.empty()) {
        result.explored_steps.push_back(explored_nodes); 

        auto pair = queue.front();
        queue.pop();

        Node node = pair.first;

        VectorOfNodes path_to_node = pair.second;
        path_to_node.push_back(node);

        if (node == finish_node) {
            result.found_path = true;
            result.path = path_to_node;
            return result;
        }

        HandleNeighbors(node, path_to_node);
    }

    return result;
}

bool BreadthFirstSearch::IsNodeExplored(const Node node) const {
    return (explored_nodes.count(node) != 0);
}

void BreadthFirstSearch::HandleNeighbors(Node current_node, VectorOfNodes path_to_current_node) {
    for (const Node neighbor: grid.GetAdjacentNodes(current_node)) {
        if (!IsNodeExplored(neighbor)) {
            queue.push({neighbor, path_to_current_node});
            explored_nodes.insert(neighbor); 
        }
    }
}
