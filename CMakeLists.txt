cmake_minimum_required(VERSION 3.16)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(gtest/lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(lab3 main.cpp binarySignal.h state.h util.h ui.cpp ui.h tests.h binarySignal.cpp util.cpp dBinarySignal.h dBinarySignal.cpp)
target_link_libraries(lab3 readline gtest gtest_main)