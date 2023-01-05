cmake_minimum_required(VERSION 3.20)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

add_compile_options(-fno-stack-check -fno-stack-protector -mno-stack-arg-probe)
add_link_options(-z muldefs -lgcc)

project(Logwin VERSION 1.0 LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

enable_testing()

# Add pdcurses library
add_library(pdcurses SHARED IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)
set_target_properties(pdcurses PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)

# Add gclados library
add_library(gclados STATIC IMPORTED)
set_target_properties(gclados PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libgclados.a)

add_subdirectory(cli)
add_subdirectory(internal)
add_subdirectory(external)
