#pragma once

#include <vector>
#include <memory>

#include "pathfinder/node.h"

namespace helpers
{
    template <typename T>
    /*
    Returns `true` if the vector contains the `target`, otherwise `false`.
    */
    bool VectorContainsItem(std::vector<T> vec, T target) {
        for (auto element: vec) {
            if (element == target) return true;
        }

        return false;
    }

    static int NumberOfNodesOfType(const std::vector<std::shared_ptr<Node>> &nodes, NodeType node_type) {
        int count = 0;

        for (auto &ptr: nodes) {
            if ((*ptr).GetNodeType() == node_type) count++;
        }

        return count;
    }
}