add_executable(pathfinder_test
  src/testtest.cpp
)
target_link_libraries(pathfinder_test PRIVATE pathfinder)
target_link_libraries(pathfinder_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(pathfinder_test)