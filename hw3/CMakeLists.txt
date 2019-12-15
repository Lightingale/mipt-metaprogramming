cmake_minimum_required(VERSION 3.14)
project(hw3)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw3 main.cpp functor.h typelist.h dispatcher.h acceptors.h visitors.h acceptors_visitors_init.h executors.h)