cmake_minimum_required(VERSION 3.10)
project(tasks)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(tasks main.cpp helpers.cpp helpers.h)