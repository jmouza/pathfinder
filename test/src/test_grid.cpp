#include <gtest/gtest.h>

#include "pathfinder/grid.h"
#include "helpers.h"

/* Constructor */
TEST(GridTest, CreateGrid)
{   
    Grid g(5, 4);
    EXPECT_EQ(g.GetNrRows(), 5);
    EXPECT_EQ(g.GetNrCols(), 4);

    EXPECT_EQ(g.GetNodes().size(), 20);
}

TEST(GridTest, InitiallyOnlyDefaultNodes)
{
    Grid g(5,4);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Default), 5*4);
}

TEST(GridTest, CreateInvalidGrid)
{   
    EXPECT_THROW(Grid(0, 1), std::invalid_argument);
    EXPECT_THROW(Grid(1, 0), std::invalid_argument);
}

/* GetNeighbours */
TEST(GridTest, GetNeighboursTopLeft) {

    Grid g(5, 6);

    Node topleft = g.GetNodeAtPosition(Position(0,0));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(topleft)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 0)));
}

TEST(GridTest, GetNeighboursUpperEdge) {
    Grid g(5, 6);
    Node upperedge = g.GetNodeAtPosition(Position(2,0));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(upperedge)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(2, 1)));
}

TEST(GridTest, GetNeighboursTopRight) {
    Grid g(5, 6);
    Node topright = g.GetNodeAtPosition(Position(5,0));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(topright)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 1)));
}

TEST(GridTest, GetNeighboursRightEdge) {
    Grid g(5, 6);
    Node rightedge = g.GetNodeAtPosition(Position(5,2));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(rightedge)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 3)));
}

TEST(GridTest, GetNeighboursBottomRight) {
    Grid g(5, 6);
    Node bottomright = g.GetNodeAtPosition(Position(5,4));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(bottomright)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 3)));
}

TEST(GridTest, GetNeighboursBottomEdge) {
    Grid g(5, 6);
    Node bottomedge = g.GetNodeAtPosition(Position(2,4));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(bottomedge)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(2, 3)));
}

TEST(GridTest, GetNeighboursBottomLeft) {
    Grid g(5, 6);
    Node bottomleft = g.GetNodeAtPosition(Position(0,4));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(bottomleft)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 2);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 3)));
}

TEST(GridTest, GetNeighboursLeftEdge) {
    Grid g(5, 6);
    Node leftedge = g.GetNodeAtPosition(Position(0,1));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(leftedge)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 1)));
}

TEST(GridTest, GetNeighboursMiddle) {
    Grid g(5, 6);
    Node middle = g.GetNodeAtPosition(Position(1,2));

    std::vector<Position> positions;
    for (const auto ptr: g.GetNeighbours(middle)) {positions.push_back(ptr->GetPosition());}

    EXPECT_EQ(positions.size(), 4);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(2, 2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 3)));
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
    Node n = Grid(5,5).GetNodeAtPosition(Position(0,0));
    EXPECT_EQ(n.GetPosition(), Position(0,0));
}

TEST(GridTest, GetNodeAtPositionLast)
{
    Node n = Grid(5,5).GetNodeAtPosition(Position(4,4));
    EXPECT_EQ(n.GetPosition(), Position(4,4));
}

TEST(GridTest, GetNodeAtPositionMiddle)
{
    Node n = Grid(5,5).GetNodeAtPosition(Position(3,2));
    EXPECT_EQ(n.GetPosition(), Position(3,2));
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
    EXPECT_EQ(g.GetStartNode().GetNodeType(), NodeType::Start);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Start), 1);
}

TEST(GridTest, SetStartNodeOverrideExistingStartNode)
{
    Grid g(5, 4);
    g.SetStartNode(Position(0,1));
    g.SetStartNode(Position(1,0));

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(1,0));
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Start), 1);
}

TEST(GridTest, SetStartNodeOverrideFinishNode)
{
    Grid g(5, 4);
    g.SetFinishNode(Position(0,1));
    g.SetStartNode(Position(0,1));

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(0,1));
    EXPECT_THROW(g.GetFinishNode(), std::runtime_error);

    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Start), 1);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Finish), 0);
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
    EXPECT_EQ(g.GetFinishNode().GetNodeType(), NodeType::Finish);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Finish), 1);
}

TEST(GridTest, SetFinishNodeOverrideExistingFinishNode)
{
    Grid g(5, 4);
    g.SetFinishNode(Position(0,1));
    g.SetFinishNode(Position(1,0));

    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(1,0));
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Finish), 1);
}

TEST(GridTest, SetFinishNodeOverrideStartNode)
{
    Grid g(5, 4);
    g.SetStartNode(Position(0,1));
    g.SetFinishNode(Position(0,1));

    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(0,1));
    EXPECT_THROW(g.GetStartNode(), std::runtime_error);

    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Finish), 1);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Start), 0);
}

TEST(GridTest, SetStartAndFinishNode)
{
    Grid g(5, 4);
    g.SetStartNode(Position(0,1));
    g.SetFinishNode(Position(1,0));

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(0,1));
    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(1,0));

    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Start), 1);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Finish), 1);
}