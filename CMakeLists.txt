cmake_minimum_required(VERSION 3.12)
project(Garbage_Collection_Cpp_Impl)

set(CMAKE_CXX_STANDARD 17)

add_executable(Garbage_Collection_Cpp_Impl main.cpp memory.h exception.h allocator.h)