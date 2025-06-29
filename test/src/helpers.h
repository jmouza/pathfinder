#pragma once

#include <vector>
#include <unordered_set>

#include "pathfinder/grid.h"
#include "pathfinder/pathfinder_result.h"

namespace TestHelpers
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

    int GetNumberOfObstaclesInGrid(const Grid grid);

    std::vector<Position> NodesToPositions(std::vector<Node> nodes);

    void SetNumberOfLinesAndColsInString(std::string str, int& nr_lines, int& nr_cols);
    Grid GetGridFromString(std::string str);

    bool ResultContainsCorrectPath(PathfinderResult result, std::vector<Position> path_positions);
    
    bool ExploredPositionsAreIncreasing(PathfinderResult result);
    bool ExploredPositionsFirstStepIsReasonable(PathfinderResult result, Node start_node);
    bool ExploredPositionsLastStepIsReasonable(PathfinderResult result, Node start_node, Node finish_node);
    bool ExploredPositionsNeverContainsObstacleNode(PathfinderResult result, Grid grid);
    bool ExploredStepContainsObstacleNode(SetOfPositions explored_step, Grid grid);
}