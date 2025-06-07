#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "pathfinder/position.h"

/* Represents the type of a `Node` on the grid. */
enum class NodeType 
{
    Default,
    Obstacle,
    Start,
    Finish
};

/* Represents a node in a 2D grid. */
class Node
{
public:
    Node(Position pos): position(pos) {}
    bool operator== (const Node &other) const {return this->position == other.GetPosition();}

    Position GetPosition() const;
    void SetNodeType(NodeType node_type_) {node_type = node_type_;}
    NodeType GetNodeType() const {return node_type;}

    struct HashFunction
    {
        size_t operator()(const Node& node) const
        {
        size_t x_hash = std::hash<int>()(node.position.value().x);
        size_t y_hash = std::hash<int>()(node.position.value().y) << 1;
        
        return x_hash ^ y_hash;
        }
    };

private:
    std::optional<Position> position;
    enum NodeType node_type = NodeType::Default;
};

