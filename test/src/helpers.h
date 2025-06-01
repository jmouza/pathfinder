#pragma once

#include <vector>

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
}