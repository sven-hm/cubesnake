cmake_minimum_required(VERSION 3.5)

project(cubesnake)
set(CUBESNAKE_VERSION 1)

add_executable(cubesnake src/main.cxx)
include_directories(src)

configure_file(
    src/cubesnake_version.h.in
    ${CMAKE_BINARY_DIR}/generated/cubesnake_version.h
    )
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -g")

#target_compile_features(cubesnake PRIVATE cxx_range_for)

