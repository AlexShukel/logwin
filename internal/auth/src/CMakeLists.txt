file(GLOB SRC_FILES *.c)

add_library(auth STATIC ${SRC_FILES})

target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/auth")
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

include(pdcurses)

target_link_libraries(auth pdcurses)

# utils
target_link_libraries(auth utils)
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")

include(argon2)

# argon2
target_link_libraries(auth argon2)
target_include_directories(auth PUBLIC "${PROJECT_SOURCE_DIR}/include/argon2")
