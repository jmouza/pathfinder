add_executable(pathfinder_test
  src/test_utils.cpp
  src/test_position.cpp
  src/test_node.cpp
  src/test_grid.cpp
)
target_link_libraries(pathfinder_test PRIVATE pathfinder)
target_link_libraries(pathfinder_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(pathfinder_test)