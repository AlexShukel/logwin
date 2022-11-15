add_executable(logwin cli.c)

target_link_libraries(logwin sha256)
target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include/sha256")
