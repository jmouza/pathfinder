#include <gtest/gtest.h>

#include "pathfinder/grid.h"
#include "helpers.h"

using namespace GridTestHelpers;

/* Verify that the test helper function work */
TEST(GridTestHelpersTest, AllNodesInGridHasCorrectNumber) 
{
    Grid grid(4, 5);
    grid.SetStartNode(Position(0,0));
    EXPECT_EQ(GetAllNodesInGrid(grid).size(), grid.GetNrOfNodes());
}

/* Constructor */
TEST(GridTest, CreateGrid)
{   
    Grid grid(4, 5);
    EXPECT_EQ(grid.GetNrCols(), 4);
    EXPECT_EQ(grid.GetNrRows(), 5);

    EXPECT_EQ(grid.GetNrOfNodes(), grid.GetNrRows() * grid.GetNrCols());
}

TEST(GridTest, InitiallyOnlyDefaultNodes)
{
    Grid grid(5,4);
    EXPECT_EQ(GetNumberOfObstaclesInGrid(grid), 0);
}

TEST(GridTest, CreateInvalidGrid)
{   
    EXPECT_THROW(Grid(0, 1), std::invalid_argument);
    EXPECT_THROW(Grid(1, 0), std::invalid_argument);
}

/* GetAdjacentNodes */
TEST(GridTest, GetAdjacentNodesTopLeft) {
    Grid grid(6, 5);

    Node topleft = grid.GetNodeAtPosition(Position(0,0));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(topleft));

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(0,1), Position(1,0)}));
}

TEST(GridTest, GetAdjacentNodesUpperEdge) {
    Grid grid(6, 5);
    Node upperedge = grid.GetNodeAtPosition(Position(2,0));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(upperedge));

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(1,0), Position(3,0), Position(2, 1)}));
}

TEST(GridTest, GetAdjacentNodesTopRight) {
    Grid grid(6, 5);
    Node topright = grid.GetNodeAtPosition(Position(5,0));
    
    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(topright));

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(4,0), Position(5, 1)}));
}

TEST(GridTest, GetAdjacentNodesRightEdge) {
    Grid grid(6, 5);
    Node rightedge = grid.GetNodeAtPosition(Position(5,2));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(rightedge));

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(4,2), Position(5,1), Position(5, 3)}));
}

TEST(GridTest, GetAdjacentNodesBottomRight) {
    Grid grid(6, 5);
    Node bottomright = grid.GetNodeAtPosition(Position(5,4));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(bottomright));

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(4,4), Position(5,3)}));
}

TEST(GridTest, GetAdjacentNodesBottomEdge) {
    Grid grid(6, 5);
    Node bottomedge = grid.GetNodeAtPosition(Position(2,4));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(bottomedge));

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(1,4), Position(3,4), Position(2,3)}));
}

TEST(GridTest, GetAdjacentNodesBottomLeft) {
    Grid grid(6, 5);
    Node bottomleft = grid.GetNodeAtPosition(Position(0,4));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(bottomleft));

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(1,4), Position(0,3)}));
}

TEST(GridTest, GetAdjacentNodesLeftEdge) {
    Grid grid(6, 5);
    Node leftedge = grid.GetNodeAtPosition(Position(0,1));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(leftedge));

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(0,0), Position(0,2), Position(1,1)}));
}

TEST(GridTest, GetAdjacentNodesMiddle) {
    Grid grid(6, 5);
    Node middle = grid.GetNodeAtPosition(Position(1,2));

    std::vector<Position> positions = NodesToPositions(grid.GetAdjacentNodes(middle));

    EXPECT_EQ(positions.size(), 4);
    EXPECT_TRUE(VectorContainsAllItems<Position>(positions, {Position(0,2), Position(2,2), Position(1,1), Position(1,3)}));
}

/* GetNodeAtPosition*/
TEST(GridTest, GetNodeAtPosition)
{
    Grid grid(4, 5);

    for (int y = 0; y < grid.GetNrRows(); y++) {
        for (int x = 0; x < grid.GetNrCols(); x++) {
            const Node node = grid.GetNodeAtPosition(Position(x, y));
            EXPECT_EQ(node.GetPosition(), Position(x,y));
        }
    }
}

TEST(GridTest, GetNodeAtPositionInvalidPos)
{
    EXPECT_THROW(Grid(5,5).GetNodeAtPosition(Position(5,5)), std::invalid_argument);
    EXPECT_THROW(Grid(5,5).GetNodeAtPosition(Position(4,5)), std::invalid_argument);
    EXPECT_THROW(Grid(5,5).GetNodeAtPosition(Position(5,4)), std::invalid_argument);
}

TEST(GridTest, GetNodeAtPositionTopLeft)
{
    Node node = Grid(5,5).GetNodeAtPosition(Position(0,0));
    EXPECT_EQ(node.GetPosition(), Position(0,0));
}

TEST(GridTest, GetNodeAtPositionLast)
{
    Node node = Grid(5,5).GetNodeAtPosition(Position(4,4));
    EXPECT_EQ(node.GetPosition(), Position(4,4));
}

TEST(GridTest, GetNodeAtPositionMiddle)
{
    Node node = Grid(5,5).GetNodeAtPosition(Position(3,2));
    EXPECT_EQ(node.GetPosition(), Position(3,2));
}

/* SetStartNode */
TEST(GridTest, StartNodeNotSet)
{
    EXPECT_THROW(Grid(5,5).GetStartNode(), std::runtime_error);
}

TEST(GridTest, SetStartNodeInvalidPosition)
{
    EXPECT_THROW(Grid(5,5).SetStartNode(Position(5,5)), std::invalid_argument);
    EXPECT_THROW(Grid(5,5).SetStartNode(Position(4,5)), std::invalid_argument);
    EXPECT_THROW(Grid(5,5).SetStartNode(Position(5,4)), std::invalid_argument);
}

TEST(GridTest, SetStartNode)
{
    Grid grid(4, 5);
    grid.SetStartNode(Position(0,1));

    EXPECT_EQ(grid.GetStartNode().GetPosition(), Position(0,1));
}

TEST(GridTest, SetStartNodeOverrideExistingStartNode)
{
    Grid grid(4, 5);
    grid.SetStartNode(Position(0,1));
    grid.SetStartNode(Position(1,0));

    EXPECT_EQ(grid.GetStartNode().GetPosition(), Position(1,0));
}

TEST(GridTest, SetStartNodeOverrideFinishNode)
{
    Grid grid(4, 5);
    grid.SetFinishNode(Position(0,1));
    grid.SetStartNode(Position(0,1));

    EXPECT_EQ(grid.GetStartNode().GetPosition(), Position(0,1));
    EXPECT_THROW(grid.GetFinishNode(), std::runtime_error);
}

/* SetFinishNode */
TEST(GridTest, FinishNodeNotSet)
{
    EXPECT_THROW(Grid(5,5).GetFinishNode(), std::runtime_error);
}

TEST(GridTest, SetFinsihNodeInvalidPosition)
{
    EXPECT_THROW(Grid(5,5).SetFinishNode(Position(5,5)), std::invalid_argument);
    EXPECT_THROW(Grid(5,5).SetFinishNode(Position(4,5)), std::invalid_argument);
    EXPECT_THROW(Grid(5,5).SetFinishNode(Position(5,4)), std::invalid_argument);
}

TEST(GridTest, SetFinishNode)
{
    Grid grid(4, 5);
    grid.SetFinishNode(Position(0,1));

    EXPECT_EQ(grid.GetFinishNode().GetPosition(), Position(0,1));
}

TEST(GridTest, SetFinishNodeOverrideExistingFinishNode)
{
    Grid grid(4, 5);
    grid.SetFinishNode(Position(0,1));
    grid.SetFinishNode(Position(1,0));

    EXPECT_EQ(grid.GetFinishNode().GetPosition(), Position(1,0));
}

TEST(GridTest, SetFinishNodeOverrideStartNode)
{
    Grid grid(4, 5);
    grid.SetStartNode(Position(0,1));
    grid.SetFinishNode(Position(0,1));

    EXPECT_EQ(grid.GetFinishNode().GetPosition(), Position(0,1));
    EXPECT_THROW(grid.GetStartNode(), std::runtime_error);
}

TEST(GridTest, SetStartAndFinishNode)
{
    Grid grid(4, 5);
    grid.SetStartNode(Position(0,1));
    grid.SetFinishNode(Position(1,0));

    EXPECT_EQ(grid.GetStartNode().GetPosition(), Position(0,1));
    EXPECT_EQ(grid.GetFinishNode().GetPosition(), Position(1,0));
}

/* SetObstacleNode */
TEST(GridTest, SetObstacleNodes)
{
    Grid grid(4, 5);

    grid.SetObstacleNode(Position(0,0));
    EXPECT_EQ(GetNumberOfObstaclesInGrid(grid), 1);
    EXPECT_TRUE(grid.GetNodeAtPosition(Position(0,0)).IsObstacle());

    grid.SetObstacleNode(Position(1,1));
    EXPECT_EQ(GetNumberOfObstaclesInGrid(grid), 2);
    EXPECT_TRUE(grid.GetNodeAtPosition(Position(1,1)).IsObstacle());
}

TEST(GridTest, SetObstacleNodeDuplicateNode)
{
    Grid grid(4, 5);

    grid.SetObstacleNode(Position(0,0));
    grid.SetObstacleNode(Position(0,0));
    EXPECT_EQ(GetNumberOfObstaclesInGrid(grid), 1);
    EXPECT_TRUE(grid.GetNodeAtPosition(Position(0,0)).IsObstacle());
}

TEST(GridTest, SetObstacleNodeOverridingStartNode)
{
    Grid grid(4, 5);
    grid.SetStartNode(Position(0,0));
    grid.SetObstacleNode(Position(0,0));

    EXPECT_THROW(grid.GetStartNode(), std::runtime_error);
    EXPECT_EQ(GetNumberOfObstaclesInGrid(grid), 1);
    EXPECT_TRUE(grid.GetNodeAtPosition(Position(0,0)).IsObstacle());
}

TEST(GridTest, SetObstacleNodeOverridingFinishNode)
{
    Grid grid(4, 5);
    grid.SetFinishNode(Position(0,0));
    grid.SetObstacleNode(Position(0,0));

    EXPECT_THROW(grid.GetFinishNode(), std::runtime_error);
    EXPECT_EQ(GetNumberOfObstaclesInGrid(grid), 1);
    EXPECT_TRUE(grid.GetNodeAtPosition(Position(0,0)).IsObstacle());
}