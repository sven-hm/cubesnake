cmake_minimum_required(VERSION 3.5)

project(cubesnake)
set(CUBESNAKE_VERSION 1)

add_executable(cubesnake
    src/main.cxx)
include_directories(src)

configure_file(
    src/cubesnake_version.h.in
    ${CMAKE_BINARY_DIR}/generated/cubesnake_version.h
    )
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread -g")

#target_compile_features(cubesnake PRIVATE cxx_range_for)

enable_testing()
find_package(GTest REQUIRED)

add_executable(test_cubesnake
    test/test_file_reader.cxx
    test/test_area.cxx
    test/test_brick.cxx
    test/test_tree.cxx
    )

target_link_libraries(test_cubesnake gtest gtest_main)
