#include <stdexcept>

#include "pathfinder/grid.h"

Grid::Grid(int nr_cols, int nr_rows) {
    if (!(nr_cols > 0 && nr_rows > 0)) {
        throw std::invalid_argument("Number of rows and columns must be greater than 0.");
    }

    this->nr_cols = nr_cols;
    this->nr_rows = nr_rows;

    CreateNodesOnGrid();
}

void Grid::CreateNodesOnGrid() {
    for (int y = 0; y < nr_rows; y++) {
        for (int x = 0; x < nr_cols; x++) {
            nodes.push_back(Node(Position(x,y)));
        }
    }
}

void Grid::SetStartNode(const Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    Node node = GetNodeAtPosition(pos);

    if (node == finish_node) {finish_node.reset();}

    start_node = node;
}

void Grid::SetFinishNode(const Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    Node node = GetNodeAtPosition(pos);

    if (node == start_node) {start_node.reset();}

    finish_node = node;
}

void Grid::SetObstacleNode(const Position pos) {
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    Node& node = nodes.at(GetVectorIndexOfPosition(pos));

    if (node == start_node) {start_node.reset();}
    if (node == finish_node) {finish_node.reset();}

    node.MakeObstacle();
}

Node Grid::GetStartNode() const {
    if (!start_node.has_value()) {
        throw std::runtime_error("Start node not set.");
    }

    return start_node.value();
}

Node Grid::GetFinishNode() const {
    if (!finish_node.has_value()) {
        throw std::runtime_error("Finish node not set.");
    }

    return finish_node.value();
}

std::vector<Node>  Grid::GetAdjacentNodes(const Node node) const {
    Position node_position = node.GetPosition();

    if (!IsPositionOnGrid(node_position)) {
        throw std::invalid_argument("Position (" + std::to_string(node_position.x) + "," + std::to_string(node_position.y) + ") is not on the grid.");
    }

    std::vector<Node> neighbours;

    Position north(node_position.x, node_position.y-1); 
    Position east(node_position.x+1, node_position.y); 
    Position south(node_position.x, node_position.y+1);
    Position west(node_position.x-1, node_position.y);

    if (IsPositionOnGrid(north)) neighbours.push_back(GetNodeAtPosition(north));
    if (IsPositionOnGrid(east)) neighbours.push_back(GetNodeAtPosition(east));
    if (IsPositionOnGrid(south)) neighbours.push_back(GetNodeAtPosition(south));
    if (IsPositionOnGrid(west)) neighbours.push_back(GetNodeAtPosition(west));

    return neighbours;
}

Node Grid::GetNodeAtPosition(const Position pos) const{
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    return nodes.at(GetVectorIndexOfPosition(pos));
}

int Grid::GetVectorIndexOfPosition(const Position pos) const{
    if (!IsPositionOnGrid(pos)) {
        throw std::invalid_argument("Position (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ") is not on the grid.");
    }

    return (pos.y * nr_cols) + pos.x;
}