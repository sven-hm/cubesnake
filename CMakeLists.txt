cmake_minimum_required(VERSION 3.5)

project(cubesnake)
set(CUBESNAKE_VERSION 0)

find_package(Threads)

add_executable(cubesnake src/cubesnake.cxx)
include_directories(src)

configure_file(
    src/cubesnake_version.h.in
    ${CMAKE_BINARY_DIR}/generated/cubesnake_version.h
    )
include_directories(${CMAKE_BINARY_DIR}/generated/)

target_compile_features(cubesnake PRIVATE cxx_range_for)

target_link_libraries(cubesnake ${CMAKE_THREAD_LIBS_INIT})
