#pragma once

#include <vector>
#include <optional>
#include <memory>

#include "pathfinder/position.h"
#include "pathfinder/constants.h"

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
    void AddNeighbor(Node neighbor); 

    std::vector<Node> GetNeighbors() const {return neighbors;}
    Position GetPosition() const;

private:
    std::optional<Position> position;
    std::vector<Node> neighbors;
};

