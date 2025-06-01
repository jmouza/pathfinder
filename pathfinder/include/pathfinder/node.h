#pragma once

#include <vector>

#include "pathfinder/position.h"
#include "pathfinder/constants.h"

class Node
{
public:
    Node(Position pos): position(pos) {}
    
    /*
    Add `neighbor` to vector of neighbors.
    @throws std::runtime_error when attempting to add neighbor while number of neighbors is already `MAX_NEIGHBORS`
    */
    void AddNeighbor(Node neighbor); 

    std::vector<Node> GetNeighbors() const {return neighbors;}
    Position GetPosition() const {return position;}

private:
    Position position;
    std::vector<Node> neighbors; 
};

