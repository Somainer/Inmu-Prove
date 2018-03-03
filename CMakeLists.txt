cmake_minimum_required(VERSION 3.9)
project(inmu_prove)

set(CMAKE_CXX_STANDARD 14)

add_executable(inmu_prove main.cpp includes.h time_testing_marco.h Tree.h RationExpr.cpp RationExpr.h helpers.cpp helpers.h)