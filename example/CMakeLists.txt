cmake_minimum_required(VERSION 3.0)

project(singleton-cpp-exmaple C CXX)
enable_language(C CXX)

set(my_headers
    ../include/singleton-cpp/singleton.h
    ./my_dll.h
    ./my_dll_api.h
)

set(my_includes
    ../include
)

add_library(my_dll SHARED my_dll.cpp ${my_headers})
target_include_directories(my_dll PRIVATE ${my_includes})
target_link_libraries(my_dll singleton)


add_executable(my_exe my_exe.cpp ${my_headers})
target_include_directories(my_exe PRIVATE ${my_includes})
target_link_libraries(my_exe singleton my_dll)
