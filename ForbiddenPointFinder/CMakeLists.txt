cmake_minimum_required(VERSION 2.7)

set(CMAKE_CXX_COMPILER_VERSION  11)
add_library(libfp ForbiddenPointFinder.cpp ForbiddenPointFinder.h CPoint.h)
