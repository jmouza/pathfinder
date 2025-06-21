#pragma once

#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>

#include "pathfinder/grid.h"
#include "pathfinder/result.h"

namespace GridTestHelpers
{
    template <typename T>
    /*
    Returns `true` if the vector contains the `target`, otherwise `false`.
    */
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

    static std::unordered_set<Node, Node::HashFunction> GetAllNodesInGrid(Grid grid) {
        std::unordered_set<Node, Node::HashFunction> set_of_nodes;
        std::queue<Node> queue;

        grid.SetStartNode(Position(0,0));
        queue.push(grid.GetStartNode());

        while (!queue.empty()) {
            Node node = queue.front();
            queue.pop();
            set_of_nodes.insert(node);

            for (const Node neighour: grid.GetAdjacentNodes(node)) {
                if (set_of_nodes.count(neighour) == 0) {
                    queue.push(neighour);
                }
            }
        }

        return set_of_nodes;
    }

    static int GetNumberOfObstaclesInGrid(const Grid grid) {
        int count = 0;

        for (const Node node: GetAllNodesInGrid(grid)) {
            if (node.IsObstacle()) count++;
        }

        return count;
    }

    static std::vector<Position> NodesToPositions(std::vector<Node> nodes) {
        std::vector<Position> positions;
        for (const auto node: nodes) {
            positions.push_back(node.GetPosition());
        }

        return positions;
    }
}

namespace PathFinderTestsHelpers {
    static void SetNumberOfLinesAndColsInString(std::string str, int& nr_lines, int& nr_cols) {
        std::stringstream ss(str);
        std::string line;

        while (std::getline(ss, line)) {
            nr_cols = line.length();
            nr_lines++;
        }
    }

    static Grid GetGridFromString(std::string str) {
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

    static bool ResultContainsCorrectPath(Result result, std::vector<Position> path_positions) {
        if (result.path.size() != path_positions.size()) return false;

        for (int i = 0; i < result.path.size(); i++) {
            if (result.path[i].GetPosition() != path_positions[i]) return false;
        }

        return true;
    }
}