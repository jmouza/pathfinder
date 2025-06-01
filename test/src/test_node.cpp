#include <gtest/gtest.h>

#include "pathfinder/node.h"

TEST(NodeTest, NewNodeHasCorrectPosition) 
{
    EXPECT_EQ(
        Node(Position(0, 0)).GetPosition(), 
        Position(0,0)
    );

    EXPECT_EQ(
        Node(Position(10, 20)).GetPosition(), 
        Position(10,20)
    );
}

TEST(NodeTest, NewNodeHasNoNeighbors) 
{
    EXPECT_TRUE(Node(Position(0,0)).GetNeighbors().empty());
}

TEST(NodeTest, AddingNeigbors)
{
    Node n(Position(1,1));

    for (int i = 1; i <= MAX_NEIGHBORS; i++) {
        n.AddNeighbor(Node(Position(0, i)));
        EXPECT_EQ(n.GetNeighbors().size(), i);
        EXPECT_EQ(n.GetNeighbors().back().GetPosition(), Position(0, i));
    }
}

TEST(NodeTest, AddingTooManyNeigbors)
{
    Node n(Position(1,1));

    for (int i = 1; i <= MAX_NEIGHBORS; i++) {
        n.AddNeighbor(Node(Position(0, i)));
    }

    EXPECT_THROW(
        n.AddNeighbor(Node(Position(0, 0))), 
        std::runtime_error
    );
}