add_library(menu STATIC menu.c)

target_include_directories(menu PUBLIC "${PROJECT_SOURCE_DIR}/include/menu" "${PROJECT_SOURCE_DIR}/include/pdcurses")
target_include_directories(menu PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

add_library(pdcurses SHARED IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)

target_link_libraries(menu pdcurses)
