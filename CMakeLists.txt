cmake_minimum_required(VERSION 3.20)

project(Logwin VERSION 1.0)
enable_language(C)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    enable_testing()
endif()

add_subdirectory(cli)
add_subdirectory(internal)
add_subdirectory(external)
