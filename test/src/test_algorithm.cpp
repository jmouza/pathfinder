#include <gtest/gtest.h>

#include "pathfinder/dfs.h"
#include "helpers.h"
#include "sample_grids.h"

TEST(HelpersTest, SanityCheckForGridCreator)
{
    Grid g = helpers::GetGridFromString(HORIZONTAL_PATH);

    EXPECT_EQ(g.GetNrCols(), 10);
    EXPECT_EQ(g.GetNrRows(), 5);
    EXPECT_EQ(g.GetNodes().size(), 50);

    EXPECT_EQ(g.GetStartNode().GetPosition(), Position(0,0));
    EXPECT_EQ(g.GetFinishNode().GetPosition(), Position(9,0));

    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Start), 1);
    EXPECT_EQ(helpers::NumberOfNodesOfType(g.GetNodes(), NodeType::Finish), 1);
}