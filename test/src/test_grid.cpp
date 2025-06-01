#include <gtest/gtest.h>

#include "pathfinder/grid.h"
#include "pathfinder/utils.h"
#include "helpers.h"

/* Constructor */
TEST(GridTest, CreateGrid)
{   
    Grid g(5, 4);
    EXPECT_EQ(g.GetNrRows(), 5);
    EXPECT_EQ(g.GetNrCols(), 4);

    EXPECT_EQ(g.GetNodes().size(), 20);

    for (auto node: g.GetNodes()) {
        EXPECT_EQ(node.GetNeighbors().size(), GetSurroundingPositions(node.GetPosition(),5,4).size());
    }    
}

TEST(GridTest, TopLeftNodeHasCorrectNeighbors) 
{
    Grid g(5, 4);

    Node topleft = g.GetNodeAtPosition(Position(0,0));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(0,1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(1,0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(1,1)));
}

TEST(GridTest, MiddleNodeHasCorrectNeighbors) 
{
    Grid g(5, 4);

    Node topleft = g.GetNodeAtPosition(Position(2,1));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(1,0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(2,0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(3,0)));

    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(1,1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(3,1)));

    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(1,2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(2,2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(3,2)));
}

TEST(GridTest, RightEdgeNodeHasCorrectNeighbors) 
{
    Grid g(5, 4);

    Node topleft = g.GetNodeAtPosition(Position(3,2));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(2,1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(3,1)));

    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(2,2)));

    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(2,3)));
    EXPECT_TRUE(helpers::VectorContainsItem<Node>(topleft.GetNeighbors(), Position(3,3)));
}

TEST(GridTest, CreateInvalidGrid)
{   
    EXPECT_THROW(Grid(0, 1), std::invalid_argument);
    EXPECT_THROW(Grid(1, 0), std::invalid_argument);
}

/* GetNodeAtPosition*/
TEST(GridTest, GetNodeAtPosition)
{
    Grid g(5, 4);
    for (int y = 0; y < g.GetNrRows(); y++) {
        for (int x = 0; x < g.GetNrCols(); x++) {
            const Node n = g.GetNodeAtPosition(Position(x, y));
            EXPECT_EQ(n.GetPosition(), Position(x,y));
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
    EXPECT_EQ(Grid(5,5).GetNodeAtPosition(Position(0,0)).GetPosition(), Position(0,0));
}

TEST(GridTest, GetNodeAtPositionLast)
{
    EXPECT_EQ(Grid(5,5).GetNodeAtPosition(Position(4,4)).GetPosition(), Position(4,4));
}

TEST(GridTest, GetNodeAtPositionMiddle)
{
    EXPECT_EQ(Grid(5,5).GetNodeAtPosition(Position(3,2)).GetPosition(), Position(3,2));
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
    Grid g(5, 4);
    g.SetStartNode(Position(0,1));

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(0,1));
}

TEST(GridTest, SetStartNodeOverrideExistingStartNode)
{
    Grid g(5, 4);
    g.SetStartNode(Position(0,1));
    g.SetStartNode(Position(1,0));

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(1,0));
}

TEST(GridTest, SetStartNodeOverrideFinishNode)
{
    Grid g(5, 4);
    g.SetFinishNode(Position(0,1));
    g.SetStartNode(Position(0,1));

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(0,1));
    EXPECT_THROW(g.GetFinishNode(), std::runtime_error);
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
    Grid g(5, 4);
    g.SetFinishNode(Position(0,1));

    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(0,1));
}

TEST(GridTest, SetFinishNodeOverrideExistingFinishNode)
{
    Grid g(5, 4);
    g.SetFinishNode(Position(0,1));
    g.SetFinishNode(Position(1,0));

    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(1,0));
}

TEST(GridTest, SetFinishNodeOverrideStartNode)
{
    Grid g(5, 4);
    g.SetStartNode(Position(0,1));
    g.SetFinishNode(Position(0,1));

    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(0,1));
    EXPECT_THROW(g.GetStartNode(), std::runtime_error);
}