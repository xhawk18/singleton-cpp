cmake_minimum_required(VERSION 3.0)

project(singleton-cpp-lib C CXX)
enable_language(C CXX)

set(my_sources
    ../include/singleton-cpp/singleton.h
    ../include/singleton-cpp/singleton_api.h
    ./singleton.cpp
)

set(my_includes
    ../include
)

add_library(singleton SHARED ${my_sources})
target_include_directories(singleton PRIVATE ${my_includes})
