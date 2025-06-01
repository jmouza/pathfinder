#include <gtest/gtest.h>

#include "helpers.h"
#include "pathfinder/utils.h"

TEST(UtilsTest, GetSurroundingPositionsZeroZero) {
    std::vector<Position> positions = GetSurroundingPositions(Position(0,0));

    EXPECT_EQ(positions.size(), 8);
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(-1, -1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(-1, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(-1, 1)));

    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, -1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(0, 1)));

    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, -1)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 0)));
    EXPECT_TRUE(helpers::VectorContainsItem<Position>(positions, Position(1, 1)));
}

TEST(UtilsTest, GetSurroundingPositionsNonZero) {
    std::vector<Position> positions = GetSurroundingPositions(Position(4,5));

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