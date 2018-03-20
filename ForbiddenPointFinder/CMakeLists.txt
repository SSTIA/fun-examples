cmake_minimum_required(VERSION 2.7)

set(CMAKE_CXX_COMPILER_VERSION  11)
add_library(libfp ForbiddenPointFinder.cpp ForbiddenPointFinder.h CPoint.h)

add_executable(libfp_test test.cpp)
target_link_libraries(libfp_test libfp)
