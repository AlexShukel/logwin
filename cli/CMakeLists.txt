add_executable(logwin cli.c)

target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include")

# sha256
target_link_libraries(logwin sha256)
target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include/sha256")

# menu
target_link_libraries(logwin menu)
target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include/menu")

# utils
target_link_libraries(logwin utils)
target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")

# auth
target_link_libraries(logwin auth)
target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include/auth")

# main
target_link_libraries(logwin main)
target_include_directories(logwin PUBLIC "${PROJECT_SOURCE_DIR}/include/main")

add_custom_command(
    TARGET logwin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/lib/pdcurses.dll" $<TARGET_FILE_DIR:logwin>
)
