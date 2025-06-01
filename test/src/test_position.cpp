#include <gtest/gtest.h>

#include "pathfinder/position.h"

TEST(PositionTest, CreatePosition) {
    EXPECT_EQ(Position(0, 0).x, 0);
    EXPECT_EQ(Position(0, 0).y, 0);

    EXPECT_EQ(Position(2, 1).x, 2);
    EXPECT_EQ(Position(2, 1).y, 1);
}
