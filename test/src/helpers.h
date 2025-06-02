#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <sstream>

#include "pathfinder/grid.h"

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

    static void SetNumberOfLinesAndColsInFile(std::string str, int& nr_lines, int& nr_cols) {
        std::stringstream ss(str);
        std::string line;

        while (std::getline(ss, line)) {
            nr_cols = line.length(); // reset every iteration...
            nr_lines++;
        }
    }

    static Grid GetGridFromString(std::string str) {
        int nr_lines = 0;
        int nr_cols = 0;
        SetNumberOfLinesAndColsInFile(str, nr_lines, nr_cols);

        Grid grid(nr_lines, nr_cols);

        std::stringstream ss(str);
        std::string line;

        int y = 0;
        while (std::getline(ss, line)) {
            int x = 0;
            for (auto symbol: line) {
                if (symbol == 'S') grid.SetStartNode(Position(x,y));
                if (symbol == 'F') grid.SetFinishNode(Position(x,y));
                x++;
            }

            y++;
        }

        return grid;
    }
}