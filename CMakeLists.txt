cmake_minimum_required(VERSION 3.26)
project(discrete_proj3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(discrete_proj3
        main.cpp
        Quotes.cpp
        Quotes.h
        Game.h
        Game.cpp
        HashMap.h
        HashMap.cpp)
