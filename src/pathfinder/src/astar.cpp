#include <unordered_set>
#include <unordered_map>
#include <cstdlib>
#include <limits>
#include <optional>
#include <cassert>
#include <algorithm>

#include "pathfinder/astar.h"

const PathfinderResult AStar::Execute() {
    if (!grid) throw std::runtime_error("Grid not set!");

    Node start_node = grid->GetStartNode();
    Node finish_node = grid->GetFinishNode();

    open_set.insert(start_node);

    PopulateGAndFScores();
    distances_from_start_node.insert_or_assign(start_node, 0);
    f_scores.insert_or_assign(start_node, DistanceBetweenNodes(start_node, finish_node));

    while (!open_set.empty()) {
        PopulateExploredPositions();

        Node current_node = NextNodeToExplore();

        if (current_node == finish_node) {
            result.found_path = true;
            ConstructPath();
            break;
        }

        open_set.erase(current_node);
        HandleNeighbors(current_node);
    }

    return result;
}

int AStar::DistanceBetweenNodes(Node source, Node target) const {
    Position sourcePos = source.GetPosition();
    Position targetPos = target.GetPosition();

    int dx = std::abs(targetPos.x - sourcePos.x);
    int dy = std::abs(targetPos.y - sourcePos.y);

    return dx + dy;
}

void AStar::PopulateGAndFScores() {
    auto nodes = grid->GetNodes();

    for (auto node: nodes) {
        distances_from_start_node.insert({node, INFINITY});
        f_scores.insert({node, INFINITY});
    }
}

void AStar::PopulateExploredPositions() {
    for (auto node: open_set) {
        explored_positions.insert(node.GetPosition());
    }
    result.explored_steps.push_back(explored_positions);
}

SetOfNodes AStar::NodesWithLowestFScores() const {
    SetOfNodes nodes_with_lowest_fcost;
    double lowest_f_score = INFINITY;

    for (auto node: open_set) {
        if (f_scores.at(node) < lowest_f_score) {
            lowest_f_score = f_scores.at(node);
            nodes_with_lowest_fcost.clear();
            nodes_with_lowest_fcost.insert(node);
        } else if (f_scores.at(node) == lowest_f_score) {
            nodes_with_lowest_fcost.insert(node);
        }
    }

    return nodes_with_lowest_fcost;
}

Node AStar::NextNodeToExplore() const {
    std::optional<Node> next_node;
    Node finish_node = grid->GetFinishNode();
    double lowest_h_score = INFINITY;

    for (auto node: NodesWithLowestFScores()) {
        double tentative_h_score = DistanceBetweenNodes(node, finish_node); 
        if (tentative_h_score < lowest_h_score) {
            lowest_h_score = tentative_h_score;
            next_node = node;
        }
    }

    return *next_node;
}

void AStar::HandleNeighbors(Node current_node) {
    Node finish_node = grid->GetFinishNode();

    for (auto neighbor: grid->GetAdjacentNodes(current_node)) {
        double tentative_g_score = distances_from_start_node.at(current_node) + DistanceBetweenNodes(current_node, neighbor);
        if (tentative_g_score < distances_from_start_node.at(neighbor)) {
            came_from.insert_or_assign(neighbor, current_node);
            
            distances_from_start_node.insert_or_assign(neighbor, tentative_g_score);
            f_scores.insert_or_assign(neighbor, tentative_g_score + DistanceBetweenNodes(neighbor, finish_node));

            if (open_set.count(neighbor) == 0) {
                open_set.insert(neighbor);
            }
        }
    }
}

void AStar::ConstructPath() {
    std::vector<Position> sequence;
    Node node = grid->GetFinishNode();
    Node came_from_node = came_from.at(node);

    sequence.push_back(node.GetPosition());
    while (came_from.count(came_from_node) != 0) {
        sequence.push_back(came_from_node.GetPosition());

        node = came_from_node;
        came_from_node = came_from.at(node);
    }
    sequence.push_back(grid->GetStartNode().GetPosition());

    std::reverse(sequence.begin(), sequence.end());

    result.path = sequence;
}

void AStar::ClearState() {
    open_set.clear();
    distances_from_start_node.clear();
    f_scores.clear();
    came_from.clear();
    explored_positions.clear();

    PathfinderAlgorithm::ClearState();
}