add_library(pdcurses SHARED IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)
