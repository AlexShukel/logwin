cmake_minimum_required(VERSION 3.20)

project(Logwin VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

enable_testing()

# Main cli
add_subdirectory(cli/src)

# SHA256
add_subdirectory(sha256/src)
add_subdirectory(sha256/test)

# AES algorithm
add_subdirectory(aes/src)
add_subdirectory(aes/test)

# Menu
add_subdirectory(menu/src)

# Utils
add_subdirectory(utils/src)
add_subdirectory(utils/test)

# Auth
add_subdirectory(auth/src)

# Main
add_subdirectory(main/src)
