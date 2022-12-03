file(GLOB SRC_FILES *.c)

add_library(main STATIC ${SRC_FILES})

target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/main")
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

include(pdcurses)

target_link_libraries(main pdcurses)

# utils
target_link_libraries(main utils)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")

# menu
target_link_libraries(main menu)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/menu")

# aes
target_link_libraries(main aes)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/aes")
