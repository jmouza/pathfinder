#pragma once

#include "pathfinder/pathfinder_algorithm.h"

#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <utility>

class Dijkstra : public PathfinderAlgorithm
{
public:
    Dijkstra(): PathfinderAlgorithm() {};
    const PathfinderResult Execute() override;

private:
    const double INFINITY = std::numeric_limits<double>::infinity();
    SetOfNodes explored_nodes;
    SetOfNodes unexplored_nodes;
    std::unordered_map<Node, double, Node::HashFunction> distance_to_start_node;
    std::unordered_map<Node, const Node*, Node::HashFunction> hop_nodes; 

    void PopulateUnexploredNodes();
    void PopulateDistancesAndHopNodes();
    void AddExploredPositionsToResultStep();
    std::optional<Node> GetClosestUnexploredNode() const;
    void HandleNeighbors(Node node);
    bool NodeIsUnexplored(Node node) const {return unexplored_nodes.count(node) != 0;}
    void ConstructPath();
};