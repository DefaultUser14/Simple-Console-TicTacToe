cmake_minimum_required(VERSION 3.10.0)
project(c++project VERSION 0.1.0 LANGUAGES C CXX)

add_executable(c++project 
src/main.cpp
src/field.cpp
src/enemy.cpp
)

include(CTest)
enable_testing()

