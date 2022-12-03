file(GLOB SRC_FILES *.c)

add_library(utils STATIC ${SRC_FILES})

target_include_directories(utils PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(utils PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")
target_include_directories(utils PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

include(pdcurses)

target_link_libraries(utils pdcurses)
