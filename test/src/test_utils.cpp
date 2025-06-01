#include <gtest/gtest.h>

#include "helpers.h"
#include "pathfinder/utils.h"

TEST(UtilsTest, GetSurroundingPositionsTopLeft) {
    std::vector<Position> positions = GetSurroundingPositions(Position(0,0), 5, 6);

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 1)));
}

TEST(UtilsTest, GetSurroundingPositionsUpperEdge) {
    std::vector<Position> positions = GetSurroundingPositions(Position(2,0), 5, 6);

    EXPECT_EQ(positions.size(), 5);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(2, 1)));
}

TEST(UtilsTest, GetSurroundingPositionsTopRight) {
    std::vector<Position> positions = GetSurroundingPositions(Position(5,0), 5, 6);

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 1)));
}

TEST(UtilsTest, GetSurroundingPositionsRightEdge) {
    std::vector<Position> positions = GetSurroundingPositions(Position(5,2), 5, 6);

    EXPECT_EQ(positions.size(), 5);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 3)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 3)));
}

TEST(UtilsTest, GetSurroundingPositionsBottomRight) {
    std::vector<Position> positions = GetSurroundingPositions(Position(5,4), 5, 6);

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 3)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 3)));
}

TEST(UtilsTest, GetSurroundingPositionsBottomEdge) {
    std::vector<Position> positions = GetSurroundingPositions(Position(2,4), 5, 6);

    EXPECT_EQ(positions.size(), 5);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 3)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(2, 3)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 3)));
}

TEST(UtilsTest, GetSurroundingPositionsBottomLeft) {
    std::vector<Position> positions = GetSurroundingPositions(Position(0,4), 5, 6);

    EXPECT_EQ(positions.size(), 3);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 3)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 3)));
}

TEST(UtilsTest, GetSurroundingPositionsLeftEdge) {
    std::vector<Position> positions = GetSurroundingPositions(Position(0,1), 5, 6);

    EXPECT_EQ(positions.size(), 5);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 2)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 2)));
}

TEST(UtilsTest, GetSurroundingPositionsMiddle) {
    std::vector<Position> positions = GetSurroundingPositions(Position(4,5), 10, 9);

    EXPECT_EQ(positions.size(), 8);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 5)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(3, 6)));

    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(4, 6)));

    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 4)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 5)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(5, 6)));
}