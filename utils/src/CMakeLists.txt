file(GLOB SRC_FILES *.c)

add_library(utils STATIC ${SRC_FILES})

target_include_directories(utils PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")
target_include_directories(utils PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

add_library(pdcurses SHARED IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)

target_link_libraries(utils pdcurses)
