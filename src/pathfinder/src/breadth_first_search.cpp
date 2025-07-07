#include <vector>

#include "pathfinder/breadth_first_search.h"

const PathfinderResult BreadthFirstSearch::Execute() {
    if (!grid) throw std::runtime_error("Grid not set!");

    Node start_node = grid->GetStartNode();
    Node finish_node = grid->GetFinishNode();

    queue.push({start_node, {}});
    explored_nodes.insert(start_node); 

    while (!queue.empty()) {
        AddExploredPositionsToResultStep();

        auto pair = queue.front();
        queue.pop();

        Node node = pair.first;

        VectorOfPositions path_to_node = pair.second;
        path_to_node.push_back(node.GetPosition());

        if (node == finish_node) {
            result.found_path = true;
            result.path = path_to_node;
            return result;
        }

        HandleNeighbors(node, path_to_node);
    }

    return result;
}

void BreadthFirstSearch::AddExploredPositionsToResultStep() {
    SetOfPositions explored_positions;
    for (auto node: explored_nodes) {
        explored_positions.insert(node.GetPosition());
    }
    result.explored_steps.push_back(explored_positions);
}

bool BreadthFirstSearch::IsNodeExplored(const Node node) const {
    return (explored_nodes.count(node) != 0);
}

void BreadthFirstSearch::HandleNeighbors(Node current_node, VectorOfPositions path_to_current_node) {
    for (const Node neighbor: grid->GetAdjacentNodes(current_node)) {
        if (!IsNodeExplored(neighbor)) {
            queue.push({neighbor, path_to_current_node});
            explored_nodes.insert(neighbor); 
        }
    }
}
