cmake_minimum_required(VERSION 3.21)
project(task_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(task_2
        src/main.cpp
        src/batch_controller.cpp
        src/file_sorter.cpp)
