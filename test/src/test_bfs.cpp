#include <gtest/gtest.h>

#include "pathfinder/breadth_first_search.h"
#include "helpers.h"
#include "sample_grids.h"

using namespace PathFinderTestsHelpers;

TEST(BFSTest, ExecuteBFSOnHorizontalSampleGrid)
{
    Grid grid = GetGridFromString(HORIZONTAL_PATH);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(ResultContainsCorrectPath(result, HORIZONTAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnVerticalSampleGrid)
{
    Grid grid = GetGridFromString(VERTICAL_PATH);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(ResultContainsCorrectPath(result, VERTICAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnShortPath)
{
    Grid grid = GetGridFromString(SHORT_PATH);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(ResultContainsCorrectPath(result, SHORT_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnImpossibleGrid1)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH1);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnImpossibleGrid2)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH2);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnImpossibleGrid3)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH3);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnPathWithObstacles1)
{
    Grid grid = GetGridFromString(PATH_WITH_OBSTACLES1);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES1_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnPathWithObstacles2)
{
    Grid grid = GetGridFromString(PATH_WITH_OBSTACLES2);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);

    EXPECT_TRUE(ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnDiagonalPath1)
{
    Grid grid = GetGridFromString(DIAGONAL_PATH1);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_EQ(result.path.size(), 7); // impossible to know exact path
    EXPECT_FALSE(result.explored_steps.empty());
}

TEST(BFSTest, ExecuteBFSOnDiagonalPath2)
{
    Grid grid = GetGridFromString(DIAGONAL_PATH2);
    BreadthFirstSearch bfs(grid);
    PathfinderResult result = bfs.Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, DIAGONAL_PATH2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
}