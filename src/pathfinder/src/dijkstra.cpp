#include <queue>
#include <algorithm>

#include "pathfinder/dijkstra.h"

const PathfinderResult Dijkstra::Execute() {
    if (!grid) throw std::runtime_error("Grid not set!");

    Node start_node = grid->GetStartNode();
    Node finish_node = grid->GetFinishNode();

    PopulateUnexploredNodes();
    PopulateDistancesAndHopNodes();
    
    distance_to_start_node.insert_or_assign(start_node, 0);

    while (!unexplored_nodes.empty()) {
        std::optional<Node> closest_node = GetClosestUnexploredNode();
        if (!closest_node.has_value()) break;

        unexplored_nodes.erase(closest_node.value());
        explored_nodes.insert(closest_node.value());
        AddExploredPositionsToResultStep();

        if (closest_node == finish_node) {
            result.found_path = true;
            break;
        }

        HandleNeighbors(closest_node.value());
    }

    if (!result.found_path) return result;

    ConstructPath();

    return result;
}

void Dijkstra::PopulateUnexploredNodes() {
    for (auto node: grid->GetNodes()) {
        if (!node.IsObstacle()) unexplored_nodes.insert(node);
    }
}

void Dijkstra::PopulateDistancesAndHopNodes() {
    for (auto node: unexplored_nodes) {
        distance_to_start_node.insert({node, INFINITY});
        hop_nodes.insert({node, nullptr});
    }
}

std::optional<Node> Dijkstra::GetClosestUnexploredNode() const {
    std::optional<Node> closest_node;

    double min_dist = INFINITY;
    for (auto node: unexplored_nodes) {
        if (distance_to_start_node.at(node) < min_dist) {
            min_dist = distance_to_start_node.at(node);
            closest_node = node;
        }
    }

    return closest_node;
}

void Dijkstra::AddExploredPositionsToResultStep() {
    SetOfPositions explored_positions;
    for (auto node: explored_nodes) {
        explored_positions.insert(node.GetPosition());
    }
    result.explored_steps.push_back(explored_positions);
}

void Dijkstra::HandleNeighbors(Node node) {
    for (auto neighbor: grid->GetAdjacentNodes(node)) {
        if (NodeIsUnexplored(neighbor)) {
            double current_distance = distance_to_start_node.at(neighbor);
            double new_distance = distance_to_start_node.at(node) + 1;
            if (new_distance < current_distance) {
                distance_to_start_node.insert_or_assign(neighbor, new_distance);
                hop_nodes.insert_or_assign(neighbor, grid->GetNodeAtPosition(node.GetPosition()));
            }
        }
    }
}

void Dijkstra::ConstructPath() {
    std::vector<Position> sequence;

    Node node = grid->GetFinishNode();
    const Node* hop_node = hop_nodes.at(node);

    while (hop_node != nullptr) {
        sequence.push_back(node.GetPosition());

        node = *hop_node;
        hop_node = hop_nodes.at(node);
    }
    sequence.push_back(grid->GetStartNode().GetPosition());
    
    std::reverse(sequence.begin(), sequence.end());

    result.path = sequence;
}