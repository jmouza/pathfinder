#include <gtest/gtest.h>

#include "pathfinder/bfs.h"
#include "helpers.h"
#include "sample_grids.h"

TEST(BFSTest, ExecuteBFSOnHorizontalSampleGrid)
{
    Grid grid = helpers::GetGridFromString(HORIZONTAL_PATH);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(helpers::ResultContainsCorrectPath(result, HORIZONTAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnVerticalSampleGrid)
{
    Grid grid = helpers::GetGridFromString(VERTICAL_PATH);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(helpers::ResultContainsCorrectPath(result, VERTICAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnShortPath)
{
    Grid grid = helpers::GetGridFromString(SHORT_PATH);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(helpers::ResultContainsCorrectPath(result, SHORT_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnImpossibleGrid1)
{
    Grid grid = helpers::GetGridFromString(IMPOSSIBLE_PATH1);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnImpossibleGrid2)
{
    Grid grid = helpers::GetGridFromString(IMPOSSIBLE_PATH2);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnImpossibleGrid3)
{
    Grid grid = helpers::GetGridFromString(IMPOSSIBLE_PATH3);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnPathWithObstacles1)
{
    Grid grid = helpers::GetGridFromString(PATH_WITH_OBSTACLES1);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(helpers::ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES1_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnPathWithObstacles2)
{
    Grid grid = helpers::GetGridFromString(PATH_WITH_OBSTACLES2);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(helpers::ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnDiagonalPath1)
{
    Grid grid = helpers::GetGridFromString(DIAGONAL_PATH1);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);
    EXPECT_EQ(result.path.size(), 7); // impossible to know exact path
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnDiagonalPath2)
{
    Grid grid = helpers::GetGridFromString(DIAGONAL_PATH2);
    BFS bfs;
    Result result = bfs.Execute(grid);

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(helpers::ResultContainsCorrectPath(result, DIAGONAL_PATH2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}