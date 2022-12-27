file(GLOB SRC_FILES *.c)

add_library(menu STATIC ${SRC_FILES})

target_include_directories(menu PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(menu PUBLIC "${PROJECT_SOURCE_DIR}/include/menu")
target_include_directories(menu PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

include(pdcurses)

target_link_libraries(menu pdcurses)

# utils
target_link_libraries(menu utils)
target_include_directories(menu PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")
