#include <gtest/gtest.h>
#include <typeinfo>

#include "pathfinder/pathfinder_context.h"
#include "pathfinder/pathfinder_algorithms.h"

class ContextTest : public testing::Test {
protected:
    PathfinderContext context;
    ExecutionParameters parameters{5, 5, Position(0, 0), Position(3, 3), {}};
};

TEST_F(ContextTest, AlgorithmNotSetExecuteAlgorithm) 
{
    EXPECT_THROW(context.ExecuteAlgorithm(parameters), std::runtime_error);
}

TEST_F(ContextTest, AlgorithmNotSetGetInstance) 
{
    EXPECT_THROW(context.GetAlgorithmInstance(), std::runtime_error);
}

TEST_F(ContextTest, SetBFS)
{
    context.SetAlgorithm([]()
        {return std::make_unique<BreadthFirstSearch>();
    });

    const char* algorithm_name = typeid(*context.GetAlgorithmInstance()).name();
    const char* expected = typeid(BreadthFirstSearch).name();

    EXPECT_EQ(algorithm_name, expected);
}

TEST_F(ContextTest, SetDijkstra)
{
    context.SetAlgorithm([]()
        {return std::make_unique<Dijkstra>();
    });

    const char* algorithm_name = typeid(*context.GetAlgorithmInstance()).name();
    const char* expected = typeid(Dijkstra).name();

    EXPECT_EQ(algorithm_name, expected);
}

TEST_F(ContextTest, OverwriteAlgorithmType)
{
    context.SetAlgorithm([]()
        {return std::make_unique<Dijkstra>();
    });

    context.SetAlgorithm([]()
        {return std::make_unique<BreadthFirstSearch>();
    });

    const char* algorithm_name = typeid(*context.GetAlgorithmInstance()).name();
    const char* expected = typeid(BreadthFirstSearch).name();

    EXPECT_EQ(algorithm_name, expected);
}

TEST_F(ContextTest, SetSameAlgorithm)
{
    context.SetAlgorithm([]()
        {return std::make_unique<Dijkstra>();
    });

    context.SetAlgorithm([]()
        {return std::make_unique<Dijkstra>();
    });

    const char* algorithm_name = typeid(*context.GetAlgorithmInstance()).name();
    const char* expected = typeid(Dijkstra).name();

    EXPECT_EQ(algorithm_name, expected);
}

TEST_F(ContextTest, ExecuteAlgorithm)
{
    context.SetAlgorithm([]()
        {return std::make_unique<Dijkstra>();
    });

    auto result = context.ExecuteAlgorithm(parameters);

    EXPECT_TRUE(result.found_path);
    EXPECT_FALSE(result.path.empty());
    EXPECT_FALSE(result.explored_steps.empty());
}