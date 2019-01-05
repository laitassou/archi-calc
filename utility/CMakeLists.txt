cmake_minimum_required(VERSION 3.0.1)




set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(utility)



set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_CXX_STANDARD 14)




include_directories(include)

add_library(utility SHARED Publisher.cpp Observer.cpp )


