#include <stdexcept>
#include <string>

#include "pathfinder/node.h"
#include "pathfinder/constants.h"

Position Node::GetPosition() const {
    if (!position.has_value()) {
        throw std::runtime_error("Position not set.");

    }
    return position.value();
}
void Node::AddNeighbor(Node neighbor) {
    if (neighbors.size() == MAX_NEIGHBORS) {
        throw std::runtime_error("Node cannot have more than " + std::to_string(MAX_NEIGHBORS) + " neighbors.");
    }
    neighbors.push_back(neighbor);
}