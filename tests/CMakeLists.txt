cmake_minimum_required(VERSION 3.10)

project(DIContainerCppTests)

#GTEST
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(runUnitTests "tests.cpp" "ComPtrTests.cpp" "component1.h" "component1.cpp" "component2.h" "component2.cpp" "component3.h" "component3.cpp" "component4.cpp" "component4.h" "CyclicInterface.h")
target_link_libraries(runUnitTests GTest::GTest GTest::Main DIContainer)

add_test( runUnitTests runUnitTests )