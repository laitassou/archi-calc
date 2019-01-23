cmake_minimum_required(VERSION 2.8.9)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(my_design)

set (CMAKE_BUILD_TYPE Debug)



set (CMAKE_CXX_STANDARD 14)

include_directories(./)

set(SOURCES app/main.cpp)


ADD_SUBDIRECTORY(utility)
ADD_SUBDIRECTORY(backend)
ADD_SUBDIRECTORY(ui)



link_directories(./ui ./utility ./backend)

add_executable(calc ${SOURCES})

target_link_libraries(calc ui utility backend)
