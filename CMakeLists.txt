cmake_minimum_required(VERSION 3.8)
project(BilliardPositioning)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Source.cpp BilliardsHandle.cpp BilliardsHandle.h)
add_executable(BilliardPositioning ${SOURCE_FILES})