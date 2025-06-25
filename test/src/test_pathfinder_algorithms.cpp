#include <gtest/gtest.h>
#include <memory>

#include "pathfinder/breadth_first_search.h"
#include "pathfinder/dijkstra.h"
#include "helpers.h"
#include "sample_grids.h"

using namespace PathFinderTestsHelpers;

TEST(PathFinderTestsHelpersTest, SanityCheckForGridCreator)
{
    Grid grid = GetGridFromString(HORIZONTAL_PATH);

    EXPECT_EQ(grid.GetNrCols(), 10);
    EXPECT_EQ(grid.GetNrRows(), 5);
    EXPECT_EQ(grid.GetNrOfNodes(), 10*5);

    EXPECT_EQ(grid.GetStartNode().GetPosition(), Position(0,0));
    EXPECT_EQ(grid.GetFinishNode().GetPosition(), Position(9,0));

    for (int x = 0; x < 10; x++) {
        EXPECT_TRUE(grid.GetNodeAtPosition(Position(x,4))->IsObstacle());
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 4; y++) {
            EXPECT_FALSE(grid.GetNodeAtPosition(Position(x,y))->IsObstacle());
        }
    }
}

template <typename T>
class PathfinderAlgorithmTest : public testing::Test {
protected:
    PathfinderAlgorithmTest() {};
    void SetAlgorithm(Grid grid) {algorithm = new T(grid);}
    ~PathfinderAlgorithmTest() override {delete algorithm;}
    PathfinderAlgorithm* algorithm;
};

typedef ::testing::Types<BreadthFirstSearch, Dijkstra> Implementations;
TYPED_TEST_SUITE(PathfinderAlgorithmTest, Implementations);

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnMiniGrid)
{
    Grid grid = GetGridFromString(MINI_GRID);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, MINI_GRID_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnHorizontalSampleGrid)
{
    Grid grid = GetGridFromString(HORIZONTAL_PATH);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, HORIZONTAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnVerticalSampleGrid)
{
    Grid grid = GetGridFromString(VERTICAL_PATH);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, VERTICAL_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnShortPath)
{
    Grid grid = GetGridFromString(SHORT_PATH);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, SHORT_PATH_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnImpossibleGrid1)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH1);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnImpossibleGrid2)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH2);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnImpossibleGrid3)
{
    Grid grid = GetGridFromString(IMPOSSIBLE_PATH3);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_FALSE(result.found_path);
    EXPECT_EQ(result.path.size(), 0);
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnPathWithObstacles1)
{
    Grid grid = GetGridFromString(PATH_WITH_OBSTACLES1);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES1_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnPathWithObstacles2)
{
    Grid grid = GetGridFromString(PATH_WITH_OBSTACLES2);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, PATH_WITH_OBSTACLES2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnDiagonalPath1)
{
    Grid grid = GetGridFromString(DIAGONAL_PATH1);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_EQ(result.path.size(), 7); // impossible to know exact path
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}

TYPED_TEST(PathfinderAlgorithmTest, ExecuteOnDiagonalPath2)
{
    Grid grid = GetGridFromString(DIAGONAL_PATH2);
    this->SetAlgorithm(grid);
    
    PathfinderResult result = this->algorithm->Execute();

    EXPECT_TRUE(result.found_path);
    EXPECT_TRUE(ResultContainsCorrectPath(result, DIAGONAL_PATH2_POSITIONS));
    EXPECT_FALSE(result.explored_steps.empty());
    EXPECT_TRUE(ExploredNodesAreIncreasing(result));
    EXPECT_TRUE(ExploredNodesFirstStepIsReasonable(result, grid.GetStartNode()));
    EXPECT_TRUE(ExploredNodesLastStepIsReasonable(result, grid.GetStartNode(), grid.GetFinishNode()));
}