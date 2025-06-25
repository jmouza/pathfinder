#pragma once

#include <vector>
#include <unordered_set>

#include "pathfinder/grid.h"
#include "pathfinder/pathfinder_result.h"

namespace GridTestHelpers
{
    template <typename T>
    bool VectorContainsItem(std::vector<T> vec, T target) {
        for (T element: vec) {
            if (element == target) return true;
        }

        return false;
    }

    template <typename T>
    bool VectorContainsAllItems(std::vector<T> vec, std::vector<T> targets) {
        for (T target: targets) {
            if (!VectorContainsItem<T>(vec, target)) return false;
        }

        return true;
    }

    template <typename T>
    bool VectorContainsAllItems(std::vector<T> vec, std::vector<T> targets);

    std::unordered_set<Node, Node::HashFunction> GetAllNodesInGrid(Grid grid);

    int GetNumberOfObstaclesInGrid(const Grid grid);

    std::vector<Position> NodesToPositions(std::vector<Node> nodes);
}

namespace PathFinderTestsHelpers {
    void SetNumberOfLinesAndColsInString(std::string str, int& nr_lines, int& nr_cols);
    Grid GetGridFromString(std::string str);
    bool ResultContainsCorrectPath(PathfinderResult result, std::vector<Position> path_positions);
    bool ExploredNodesAreIncreasing(PathfinderResult result);
    bool ExploredNodesFirstStepIsReasonable(PathfinderResult result, Node start_node);
    bool ExploredNodesLastStepIsReasonable(PathfinderResult result, Node start_node, Node finish_node);
}