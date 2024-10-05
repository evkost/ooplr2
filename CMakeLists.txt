cmake_minimum_required(VERSION 3.28)
project(ooplr2)

#setup vars
set(CMAKE_CXX_STANDARD 20)
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

# main sources
add_library(ooplr2_include
        ${INCLUDE_DIR}/money.h
)
add_library(ooplr2_lib
        ${LIB_DIR}/money.cpp
)
target_link_libraries(
        ooplr2_include
        ooplr2_lib
)

#setup googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/0953a17a4281fc26831da647ad3fcd5e21e6473b.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

#test sources
add_executable(ooplr2_tests
        ${TEST_DIR}/money_tests.cpp
)
target_link_libraries(
        ooplr2_tests
        ooplr2_include
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(ooplr2_tests)
