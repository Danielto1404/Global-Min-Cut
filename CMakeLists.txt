cmake_minimum_required(VERSION 3.15)
project(Global_Min_Cut)

set(CMAKE_CXX_STANDARD 17)

add_executable(Global_Min_Cut main.cpp headers/STOER_WAGNER_ALGORITHM.h sources/STOER_WAGNER_ALGORITHM.cpp sources/graph.cpp headers/graph.h)