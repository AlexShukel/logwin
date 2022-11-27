cmake_minimum_required(VERSION 3.20)

project(Logwin VERSION 1.0)

# Main cli
add_subdirectory(cli/src)

# SHA256
add_subdirectory(sha256/src)
add_subdirectory(sha256/test)

# Menu
add_subdirectory(menu/src)

# Utils
add_subdirectory(utils/src)
