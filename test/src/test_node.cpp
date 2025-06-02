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

TEST(NodeTest, AddingNeigbors)
{
    Node n(Position(1,1));
    std::vector<std::unique_ptr<Node>> neighbors; // owns the node pointers

    for (int i = 1; i <= MAX_NEIGHBORS; i++) {
        neighbors.push_back(std::make_unique<Node>(Position(0,i)));
        n.AddNeighbor(neighbors.back().get());

        EXPECT_EQ(n.GetNeighbors().size(), i);

        auto node = *(n.GetNeighbors().back());
        EXPECT_EQ(node.GetPosition(), Position(0, i));
    }
}

TEST(NodeTest, AddingTooManyNeigbors)
{
    Node n(Position(1,1));
    std::vector<std::unique_ptr<Node>> neighbors; // owns the node pointers

    for (int i = 1; i <= MAX_NEIGHBORS; i++) {
        neighbors.push_back(std::make_unique<Node>(Position(0,i)));
        n.AddNeighbor(neighbors.back().get());
    }

    Node extra_neighbor(Position(0,0));
    EXPECT_THROW(
        n.AddNeighbor(&extra_neighbor), 
        std::runtime_error
    );
}