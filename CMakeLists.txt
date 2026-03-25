cmake_minimum_required(VERSION 4.0)
project(LmaoApp)

set(CMAKE_CXX_STANDARD 26)

add_executable(LmaoApp main.cpp
        main.cpp)

target_link_libraries(LmaoApp stdc++exp)