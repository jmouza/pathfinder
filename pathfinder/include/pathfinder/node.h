#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "pathfinder/position.h"
#include "pathfinder/constants.h"

/* Represents the type of a `Node` on the grid. */
enum class NodeType 
{
    Default,
    Obstacle,
    Start,
    Finish,
    Path,
    Discovered
};

/* Represents a node in a 2D grid. */
class Node
{
public:
    Node(Position pos): position(pos) {}
    bool operator== (const Node &other) const {return this->position == other.GetPosition();}

    /*
    Add `neighbor` to vector of neighbors.
    @throws `std::runtime_error` when attempting to add neighbor while number of neighbors is already `MAX_NEIGHBORS`
    */
    void AddNeighbor(Node* neighbor); 

    std::vector<Node*> GetNeighbors() const {return neighbors;}
    Position GetPosition() const;
    void SetNodeType(NodeType node_type_) {node_type = node_type_;}
    NodeType GetNodeType() const {return node_type;}

private:
    std::optional<Position> position;
    std::vector<Node*> neighbors;
    enum NodeType node_type = NodeType::Default;
};

