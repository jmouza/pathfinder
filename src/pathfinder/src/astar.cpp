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

    const double INFINITY = std::numeric_limits<double>::infinity();

    Node start_node = grid->GetStartNode();
    Node finish_node = grid->GetFinishNode();
    auto nodes = grid->GetNodes();

    SetOfNodes open_set;
    open_set.insert(start_node);

    std::unordered_map<Node, double, Node::HashFunction> g_scores; /* Distance to start node */
    std::unordered_map<Node, int, Node::HashFunction> f_scores; /* g_scores[n] + distance_to_finish[n] */

    for (auto node: nodes) {
        g_scores.insert({node, INFINITY});
        f_scores.insert({node, INFINITY});
    }
    g_scores.insert_or_assign(start_node, 0);
    f_scores.insert_or_assign(start_node, DistanceBetweenNodes(start_node, finish_node));

    std::unordered_map<Node, Node, Node::HashFunction> came_from;

    SetOfPositions explored_positions;

    while (!open_set.empty()) {
        /* Explored positions */
        for (auto node: open_set) {
            explored_positions.insert(node.GetPosition());
        }
        result.explored_steps.push_back(explored_positions);

        /* Node in open_set with lowest fscore */
        SetOfNodes nodes_with_lowest_fcost;
        double min_distance = INFINITY;
        for (auto node: open_set) {
            if (f_scores.at(node) < min_distance) {
                min_distance = f_scores.at(node);
                nodes_with_lowest_fcost.clear();
                nodes_with_lowest_fcost.insert(node);
            } else if (f_scores.at(node) == min_distance) {
                nodes_with_lowest_fcost.insert(node);
            }
        }
        std::optional<Node> closest_node;
        min_distance = INFINITY;
        for (auto node: nodes_with_lowest_fcost) {
            if (DistanceBetweenNodes(node, finish_node) < min_distance) {
                min_distance = DistanceBetweenNodes(node, finish_node);
                closest_node = node;
            }
        }
        assert(closest_node);

        /* Check for finish node */
        if (closest_node == finish_node) {
            result.found_path = true;

            /* construct path */
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

            break;
        }

        open_set.erase(*closest_node);

        /* handle neighbors */
        for (auto neighbor: grid->GetAdjacentNodes(*closest_node)) {
            double tentative_gscore = g_scores.at(*closest_node) + DistanceBetweenNodes(*closest_node, neighbor);
            if (tentative_gscore < g_scores.at(neighbor)) {
                came_from.insert_or_assign(neighbor, *closest_node);
                g_scores.insert_or_assign(neighbor, tentative_gscore);
                f_scores.insert_or_assign(neighbor, tentative_gscore + DistanceBetweenNodes(neighbor, finish_node));

                if (open_set.count(neighbor) == 0) {
                    open_set.insert(neighbor);
                }
            }
        }
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

void AStar::ConstructPath() {
    return;
}