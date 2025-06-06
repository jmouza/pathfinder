#include <stdexcept>
#include <string>

#include "pathfinder/node.h"

Position Node::GetPosition() const {
    if (!position.has_value()) {
        throw std::runtime_error("Position not set.");

    }
    return position.value();
}