#pragma once

#include <vector>
#include <optional>

#include "pathfinder/node.h"

using VectorOfNodes = std::vector<Node>;

/* 
Represents a 2D grid of `Node` objects, with (0, 0) being the top-left node. 
A grid cannot be resized.
*/
class Grid 
{
public:
    /*
    @throws `std::invalid_argument` if `nr_rows` or `nr_cols` is not positive.
    */
    Grid(int nr_cols, int nr_rows);

    /*
    If given position is a `finish_node` it will be overriden and `finish_node` will be unset.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    void SetStartNode(const Position pos);

    /*
    If given position is a `start_node` it will be overriden and `start_node` will be unset.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    void SetFinishNode(const Position pos);

    /*
    Make node at given position an obstacle. 
    If given node is the `start_node` or `finish_node`, it will be unset as being so.
    @throws `std::invalid_argument` if position is not on the grid.
    */
    void SetObstacleNode(const Position pos);

    /*
    @throws `std::runtime_error` if `start_node` not set.
    */
    Node GetStartNode() const;

    /*
    @throws `std::runtime_error` if `finish_node` not set.
    */
    Node GetFinishNode() const;

    /*
    Returns non-obstacle adjacent nodes.
    @throws `std::invalid_argument` if node's position is not on the grid.
    */
    std::vector<Node> GetAdjacentNodes(const Node node) const;

    /*
    @throws `std::invalid_argument` if position is not on the grid.
    */
    const Node* GetNodeAtPosition(const Position pos) const;

    /*
    @throws `std::invalid_argument` if position is not on the grid.
    */
    int GetVectorIndexOfPosition(const Position pos) const;

    int GetNrCols() const {return nr_cols;}
    int GetNrRows() const {return nr_rows;}
    VectorOfNodes GetNodes() const {return nodes;}

private:
    int nr_cols;
    int nr_rows;

    std::optional<Node> start_node;
    std::optional<Node> finish_node;
    VectorOfNodes nodes; /* Represents the nodes in the 2D grid. */

    bool IsPositionOnGrid(const Position pos) const {return pos.x >= 0 && pos.y >= 0 && pos.x < nr_cols && pos.y < nr_rows;}
    bool IsPositionAnObstacle(const Position pos) const {return GetNodeAtPosition(pos)->IsObstacle();}
    void CreateNodesOnGrid();
};