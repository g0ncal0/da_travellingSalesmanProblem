cmake_minimum_required(VERSION 3.26)
project(DAProject2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DAProject2 main.cpp
        Graph/Graph.cpp
        Graph/Graph.h
        Algorithms/Algorithms.h
        Algorithms/Algorithms.cpp
        Parser.h
        Parser.cpp
        Menu.cpp
        Menu.h)
