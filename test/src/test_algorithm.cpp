#include <gtest/gtest.h>

#include "helpers.h"
#include "sample_grids.h"

using namespace PathFinderTestsHelpers;

TEST(HelpersTest, SanityCheckForGridCreator)
{
    Grid grid = GetGridFromString(HORIZONTAL_PATH);

    EXPECT_EQ(grid.GetNrCols(), 10);
    EXPECT_EQ(grid.GetNrRows(), 5);
    EXPECT_EQ(grid.GetNrOfNodes(), 10*5);

    EXPECT_EQ(grid.GetStartNode().GetPosition(), Position(0,0));
    EXPECT_EQ(grid.GetFinishNode().GetPosition(), Position(9,0));

    for (int x = 0; x < 10; x++) {
        EXPECT_TRUE(grid.GetNodeAtPosition(Position(x,4)).IsObstacle());
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 4; y++) {
            EXPECT_FALSE(grid.GetNodeAtPosition(Position(x,y)).IsObstacle());
        }
    }
}