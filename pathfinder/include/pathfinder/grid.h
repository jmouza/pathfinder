#pragma once

#include <vector>
#include <optional>

#include "pathfinder/node.h"

using NodePointer = std::shared_ptr<Node>;
using VectorOfNodePointers = std::vector<NodePointer>;

/* 
Represents a 2D grid of `Node` objects, with (0, 0) being the top-left node. 
A grid cannot be resized.
*/
class Grid 
{
public:
    /*
    Create a grid of size `(nr_rows, nr_cols).`
    @throws `std::invalid_argument` if `nr_rows` or `nr_cols` is not positive.
    */
    Grid(int nr_rows, int nr_cols);

    /*
    Set `start_node`. 
    It will override an existing `start_node`.
    If given position is a `finish_node` it will be overriden and `finish_node` will be unset.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    void SetStartNode(const Position pos);

    /*
    Set `finish_node`. 
    It will override an existing `finish_node`.
    If given position is a `start_node` it will be overriden and `start_node` will be unset.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    void SetFinishNode(const Position pos);

    /*
    Make node at given position an obstacle. 
    If given node is the `start_node` or `finish_node`, it will be overriden
    and `start_node` or `finish_node` will be unset.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    void SetObstacleNode(const Position pos);

    /*
    Get the current `start_node`.
    @throws `std::runtime_error` if `start_node` not set.
    */
    Node& GetStartNode() const;

    /*
    Get the current `finish_node`.
    @throws `std::runtime_error` if `finish_node` not set.
    */
    Node& GetFinishNode() const;

    /*
    Get node at given position from the vector of nodes.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    Node& GetNodeAtPosition(const Position pos) const;

    /*
    Returns the (at most) four neighbours of the given node on the grid.
    Neighbours that are not on the grid are not included in the output.
    @throws `std::invalid_argument` if node's position is not on the grid.
    */
    VectorOfNodePointers GetNeighbours(const Node node) const;

    int GetNrCols() const {return nr_cols;}
    int GetNrRows() const {return nr_rows;}
    const VectorOfNodePointers& GetNodes() const {return nodes;}

private:
    int nr_cols;
    int nr_rows;

    std::optional<Position> start_node_position;
    std::optional<Position> finish_node_position;
    VectorOfNodePointers nodes; /* Represents the nodes in the 2D grid. */

    bool IsPositionOnGrid(const Position pos) const {return pos.x >= 0 && pos.y >= 0 && pos.x < nr_cols && pos.y < nr_rows;}
    void CreateGrid();
    NodePointer GetNodePointerAtPosition(const Position pos) const;
};