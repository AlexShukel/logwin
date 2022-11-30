file(GLOB SRC_FILES *.c)

add_library(main STATIC ${SRC_FILES})

target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/main")
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

add_library(pdcurses SHARED IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)
target_link_libraries(main pdcurses)

# utils
target_link_libraries(main utils)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")

# menu
target_link_libraries(main menu)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/include/menu")
