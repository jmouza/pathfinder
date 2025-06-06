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

TEST(NodeTest, NewNodeHasDefaultType) 
{
    EXPECT_EQ(Node(Position(0,0)).GetNodeType(), NodeType::Default);
}

TEST(NodeTest, OverrideNodeType) 
{
    Node n(Position(0,0));
    n.SetNodeType(NodeType::Start);
    EXPECT_EQ(n.GetNodeType(), NodeType::Start);
    n.SetNodeType(NodeType::Default);
    EXPECT_EQ(n.GetNodeType(), NodeType::Default);
}