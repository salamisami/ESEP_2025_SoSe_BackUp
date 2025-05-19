cmake_minimum_required(VERSION 3.14)
project(StateMachineTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option 1: Use the simpler GTest integration
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/../output
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}/../src/statemachine
    ${googletest_SOURCE_DIR}/googletest/include
    ${googletest_SOURCE_DIR}/googlemock/include
)

# Source files
set(TEST_SOURCES FSM_SwitchModus_test.cpp)
set(PRODUCTION_SOURCES
    ../src/statemachine/FBM.cpp
    ../src/statemachine/BetriebsModus.cpp
    ../src/statemachine/RuheModus.cpp
    ../src/statemachine/ServiceModus.cpp
)

# Create test executable
add_executable(FSM_SwitchModus_test
    ${TEST_SOURCES}
    ${PRODUCTION_SOURCES}
)

# Enable testing mode for FSM_SwitchModus_test
target_compile_definitions(FSM_SwitchModus_test PRIVATE ENABLE_STATE_TESTING)

# Add include directories
target_include_directories(FSM_SwitchModus_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc  # Assuming your FBM.h is in a src directory
    ${CMAKE_CURRENT_SOURCE_DIR}         # For headers in the test directory
)

target_link_libraries(FSM_SwitchModus_test PRIVATE
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(FSM_SwitchModus_test)