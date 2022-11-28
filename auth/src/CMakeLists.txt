file(GLOB SRC_FILES *.c)

add_library(auth STATIC ${SRC_FILES})

target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/auth")
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

add_library(pdcurses SHARED IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/pdcurses.dll)
target_link_libraries(auth pdcurses)

# utils
target_link_libraries(auth utils)
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")

# sha256
target_link_libraries(auth sha256)
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/sha256")
