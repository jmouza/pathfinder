#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "pathfinder/position.h"

/* Represents a node in a 2D grid. */
class Node
{
public:
    Node(Position pos): position(pos) {}
    bool operator== (const Node &other) const {return this->position == other.GetPosition();}

    Position GetPosition() const;
    void MakeObstacle() {is_obstacle = true;}
    bool IsObstacle() const {return is_obstacle;}

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
    bool is_obstacle = false;
};

