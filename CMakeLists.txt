cmake_minimum_required(VERSION 2.8.9)
project(MersenneTwisterSerialCpp)
include_directories(include)

#file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_executable(MersenneTwisterSerialCppTest "tests/testMersenneTwister.cpp")
add_executable(MersenneTwisterSerialCppTestWithCatch "tests/catchTest.cpp")
