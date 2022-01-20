
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(build)
file(GLOB_RECURSE SRC_FILES src/*.cpp )
add_executable(build main.cpp ${SRC_FILES})
target_include_directories(build PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)




