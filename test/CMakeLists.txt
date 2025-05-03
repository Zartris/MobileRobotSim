# Find GTest package
find_package(GTest REQUIRED)

# Define test source files
set(TEST_SOURCES
    simulation_engine_test.cpp
    environment_test.cpp
    point_robot_test.cpp
    system_state_test.cpp
)

# Create test executable
add_executable(mobilerobotsim_tests ${TEST_SOURCES})

# Link with the library under test and GTest
target_link_libraries(mobilerobotsim_tests
    PRIVATE
    mobilerobotsim
    GTest::GTest
    GTest::Main
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(mobilerobotsim_tests)

# Create test data directory in build directory
add_custom_command(
    TARGET mobilerobotsim_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test_data
)

# Copy test data files if any
# add_custom_command(
#     TARGET mobilerobotsim_tests POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/test_data
# )

# Define a custom target for running tests
add_custom_target(run_tests
    COMMAND mobilerobotsim_tests
    DEPENDS mobilerobotsim_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
