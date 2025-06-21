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

TEST(NodeTest, MakeNodeObstacle) 
{
    Node node = Node(Position(0,0));
    node.MakeObstacle();
    EXPECT_TRUE(node.IsObstacle());
}

TEST(NodeTest, MakeNodeObstacleTwice) 
{
    Node node = Node(Position(0,0));
    node.MakeObstacle();
    node.MakeObstacle();
    EXPECT_TRUE(node.IsObstacle());
}