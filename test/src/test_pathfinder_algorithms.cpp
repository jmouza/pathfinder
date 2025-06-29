#include <gtest/gtest.h>
#include <memory>

#include "pathfinder/pathfinder_algorithms.h"
#include "helpers.h"
#include "sample_grids.h"

using namespace TestHelpers;

template <typename T>
class PathfinderAlgorithmTest : public testing::Test {
protected:
    PathfinderAlgorithmTest(): algorithm(new T()) {};

    ~PathfinderAlgorithmTest() override {delete algorithm;}
    PathfinderAlgorithm* algorithm;
};

typedef ::testing::Types<BreadthFirstSearch, Dijkstra> Implementations;
TYPED_TEST_SUITE(PathfinderAlgorithmTest, Implementations);

TYPED_TEST(PathfinderAlgorithmTest, GridNotSet) {
    Grid grid = GetGridFromString(MINI_GRID);
    
    EXPECT_THROW(this->algorithm->Execute(), std::runtime_error);
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnMiniGrid)
{
    Grid grid = GetGridFromString(MINI_GRID);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, MINI_GRID_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnHorizontalSampleGrid)
{
    Grid grid = GetGridFromString(HORIZONTAL_PATH);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, HORIZONTAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnVerticalSampleGrid)
{
    Grid grid = GetGridFromString(VERTICAL_PATH);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, VERTICAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnShortPath)
{
    Grid grid = GetGridFromString(SHORT_PATH);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, SHORT_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnImpossibleGrid1)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH1);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnImpossibleGrid2)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH2);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnImpossibleGrid3)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH3);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnPathWithObstacles1)
{
    Grid grid = GetGridFromString(PATH_WITH_OBSTACLES1);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES1_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnPathWithObstacles2)
{
    Grid grid = GetGridFromString(PATH_WITH_OBSTACLES2);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnDiagonalPath1)
{
    Grid grid = GetGridFromString(DIAGONAL_PATH1);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_EQ(result.path.size(), 7); // impossible to know exact path
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnDiagonalPath2)
{
    Grid grid = GetGridFromString(DIAGONAL_PATH2);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, DIAGONAL_PATH2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnGridWithStartPointInMiddle)
{
    Grid grid = GetGridFromString(START_POINT_IN_THE_MIDDLE_STRAIGHT_LINE);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, START_POINT_IN_THE_MIDDLE_STRAIGHT_LINE_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnGridWithStartPointInMiddleLoop)
{
    Grid grid = GetGridFromString(START_POINT_IN_THE_MIDDLE_LOOP);
    this->algorithm->SetGrid(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, START_POINT_IN_THE_MIDDLE_LOOP_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesNeverContainsObstacleNode(result));
}