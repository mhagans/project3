cmake_minimum_required(VERSION 3.1)
project(Project3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LexicalAnalyzer.cpp SyntaxAnalyzer.cpp)
add_executable(Project3 ${SOURCE_FILES})