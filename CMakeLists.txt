cmake_minimum_required(VERSION 3.20)

project(Logwin VERSION 1.0)

# TODO: configure builds for debug and release
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

enable_testing()

add_subdirectory(cli)

add_subdirectory(internal)

add_subdirectory(external)
