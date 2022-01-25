cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(SBomber)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(SBomber ${SOURCES})
