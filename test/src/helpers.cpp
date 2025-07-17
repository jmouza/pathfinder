#include <queue>
#include <iostream>
#include <string>
#include <sstream>

#include "helpers.h"

namespace TestHelpers
{
    int GetNumberOfObstaclesInGrid(const Grid grid) {
        int count = 0;

        for (const Node node: grid.GetNodes()) {
            if (node.IsObstacle()) count++;
        }

        return count;
    }

    std::vector<Position> NodesToPositions(std::vector<Node> nodes) {
        std::vector<Position> positions;
        for (const auto node: nodes) {
            positions.push_back(node.GetPosition());
        }

        return positions;
    }

    void SetNumberOfLinesAndColsInString(std::string str, int& nr_lines, int& nr_cols) {
        std::stringstream ss(str);
        std::string line;

        while (std::getline(ss, line)) {
            nr_cols = line.length();
            nr_lines++;
        }
    }

    Grid GetGridFromString(std::string str) {
        int nr_lines = 0;
        int nr_cols = 0;
        SetNumberOfLinesAndColsInString(str, nr_lines, nr_cols);

        Grid grid(nr_cols, nr_lines);

        std::stringstream ss(str);
        std::string line;

        int y = 0;
        while (std::getline(ss, line)) {
            int x = 0;
            for (auto symbol: line) {
                if (symbol == 'S') grid.SetStartNode(Position(x,y));
                if (symbol == 'F') grid.SetFinishNode(Position(x,y));
                if (symbol == 'O') grid.SetObstacleNode(Position(x,y));
                x++;
            }

            y++;
        }

        return grid;
    }

    bool ResultContainsCorrectPath(PathfinderResult result, std::vector<Position> path_positions) {
        if (result.path.size() != path_positions.size()) return false;

        for (size_t i = 0; i < result.path.size(); i++) {
            if (result.path[i] != path_positions[i]) return false;
        }

        return true;
    }

    bool ExploredPositionsAreIncreasing(PathfinderResult result) {
        int count = -1;

        for (auto set_of_positions: result.explored_steps) {
            if (static_cast<int>(set_of_positions.size()) < count) return false;
            count = static_cast<int>(set_of_positions.size());
        }

        return true;
    }

    bool ExploredPositionsFirstStepIsReasonable(PathfinderResult result, Node start_node) {
        if (result.explored_steps.empty()) return false;

        bool starts_with_one_node = (result.explored_steps.front().size() == 1);
        bool starts_with_start_node = (result.explored_steps.front().count(start_node.GetPosition()) == 1);

        return starts_with_one_node && starts_with_start_node;
    }

    bool ExploredPositionsLastStepIsReasonable(PathfinderResult result, Node start_node, Node finish_node) {
        if (result.explored_steps.empty()) return false;

        bool ends_with_more_than_one_node = (result.explored_steps.back().size() > 1);
        bool last_step_contains_start_node = (result.explored_steps.back().count(start_node.GetPosition()) == 1);
        bool last_step_contains_finish_node = (result.explored_steps.back().count(finish_node.GetPosition()) == 1);

        return ends_with_more_than_one_node && last_step_contains_start_node && last_step_contains_finish_node;
    }

    bool ExploredPositionsNeverContainsObstacleNode(PathfinderResult result, Grid grid) {
        for (auto set: result.explored_steps) {
            if (ExploredStepContainsObstacleNode(set, grid)) return false;
        }

        return true;
    }

    bool ExploredStepContainsObstacleNode(SetOfPositions explored_step, Grid grid) {
        for (auto position: explored_step) {
            if (grid.GetNodeAtPosition(position)->IsObstacle()) return true;
        }

        return false;
    }
}