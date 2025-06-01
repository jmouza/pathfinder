#include <stdexcept>

#include "pathfinder/grid.h"
#include "pathfinder/utils.h"

Grid::Grid(int nr_rows, int nr_cols) {
    if (!(nr_rows > 0 && nr_cols > 0)) {
        throw std::invalid_argument("Number of rows and columns must be greater than 0.");
    }

    this->nr_rows = nr_rows;
    this->nr_cols = nr_cols;

    CreateGrid();
}

void Grid::CreateGrid() {
    // Create nodes
    for (int y = 0; y < nr_rows; y++) {
        for (int x = 0; x < nr_cols; x++) {
            nodes.push_back(Node(Position(x, y)));
        }
    }

    // Link neighbors
    for (Node& node: nodes) {
        AddNeighbors(node);
    }
}

void Grid::AddNeighbors(Node& node) {
    auto neighbors_pos = GetSurroundingPositions(node.GetPosition(), nr_rows, nr_cols);
    for (Position pos : neighbors_pos) {
        node.AddNeighbor(GetNodeAtPosition(pos));
    }
}

void Grid::SetStartNode(Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    if (finish_node_position == pos) {finish_node_position.reset();}

    start_node_position = pos;
}

void Grid::SetFinishNode(Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    if (start_node_position == pos) {start_node_position.reset();}

    finish_node_position = pos;
}

const Node& Grid::GetStartNode() const {
    if (!start_node_position.has_value()) {
        throw std::runtime_error("Start node not set.");
    }

    return GetNodeAtPosition(start_node_position.value());
}

const Node& Grid::GetFinishNode() const {
    if (!finish_node_position.has_value()) {
        throw std::runtime_error("Finish node not set.");
    }

    return GetNodeAtPosition(finish_node_position.value());
}

const Node& Grid::GetNodeAtPosition(Position pos) const {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    int vector_index = (pos.y * nr_cols) + pos.x;

    return nodes[vector_index];
}