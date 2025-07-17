#pragma once

#include "pathfinder/pathfinder_algorithm.h"

class AStar : public PathfinderAlgorithm
{
public:
    AStar(): PathfinderAlgorithm() {};
    const PathfinderResult Execute() override;

private:
    const double INFINITY = std::numeric_limits<double>::infinity();
    SetOfNodes open_set;
    std::unordered_map<Node, double, Node::HashFunction> distances_from_start_node; /* g(n): Distance from start node */
    std::unordered_map<Node, double, Node::HashFunction> f_scores; /* distances_from_start_node[n] + distance_to_finish[n] */  
    std::unordered_map<Node, Node, Node::HashFunction> came_from;
    SetOfPositions explored_positions;

    int DistanceBetweenNodes(Node source, Node target) const;
    void PopulateGAndFScores();
    void PopulateExploredPositions();
    Node NextNodeToExplore() const;
    SetOfNodes NodesWithLowestFScores() const;
    void HandleNeighbors(Node current_node);
    void ConstructPath();
};