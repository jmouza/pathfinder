#include <stdexcept>

#include "pathfinder/grid.h"

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
            nodes.push_back(std::make_shared<Node>(Position(x,y)));
        }
    }
}

void Grid::SetStartNode(const Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    if (finish_node_position == pos) {finish_node_position.reset();}
    if (start_node_position.has_value()) {GetStartNode().SetNodeType(NodeType::Default);}

    start_node_position = pos;
    GetNodeAtPosition(start_node_position.value()).SetNodeType(NodeType::Start);
}

void Grid::SetFinishNode(const Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    if (start_node_position == pos) {start_node_position.reset();}
    if (finish_node_position.has_value()) {GetFinishNode().SetNodeType(NodeType::Default);}

    finish_node_position = pos;
    GetNodeAtPosition(finish_node_position.value()).SetNodeType(NodeType::Finish);
}

void Grid::SetObstacleNode(const Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    if (start_node_position == pos) {start_node_position.reset();}
    if (finish_node_position == pos) {finish_node_position.reset();}

    GetNodeAtPosition(pos).SetNodeType(NodeType::Obstacle);
}

Node& Grid::GetStartNode() const {
    if (!start_node_position.has_value()) {
        throw std::runtime_error("Start node not set.");
    }

    return GetNodeAtPosition(start_node_position.value());
}

Node& Grid::GetFinishNode() const {
    if (!finish_node_position.has_value()) {
        throw std::runtime_error("Finish node not set.");
    }

    return GetNodeAtPosition(finish_node_position.value());
}

Node& Grid::GetNodeAtPosition(const Position pos) const {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    return *GetNodePointerAtPosition(pos);
}

NodePointer Grid::GetNodePointerAtPosition(const Position pos) const {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    int vector_index = (pos.y * nr_cols) + pos.x;

    return nodes[vector_index];
}

VectorOfNodePointers Grid::GetNeighbours(const Node node) const {
    Position node_position = node.GetPosition();

    if (!IsPositionOnGrid(node_position)) {
        throw std::invalid_argument("Position (" + std::to_string(node_position.x) + "," + std::to_string(node_position.y) + ") is not on the grid.");
    }

    VectorOfNodePointers neighbours;

    Position north(node_position.x, node_position.y-1); 
    Position east(node_position.x+1, node_position.y); 
    Position south(node_position.x, node_position.y+1);
    Position west(node_position.x-1, node_position.y);

    if (IsPositionOnGrid(north)) neighbours.push_back(GetNodePointerAtPosition(north));
    if (IsPositionOnGrid(east)) neighbours.push_back(GetNodePointerAtPosition(east));
    if (IsPositionOnGrid(south)) neighbours.push_back(GetNodePointerAtPosition(south));
    if (IsPositionOnGrid(west)) neighbours.push_back(GetNodePointerAtPosition(west));

    return neighbours;
}