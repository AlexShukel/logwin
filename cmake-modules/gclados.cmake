file(GLOB SRC_FILES *.test.c)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/entry.c
    COMMAND gclados generate ${CMAKE_CURRENT_SOURCE_DIR}/*.test.c --output ${CMAKE_CURRENT_SOURCE_DIR}/entry.c
    DEPENDS ${SRC_FILES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# TODO: check if it is possible to move this configuration in root CMakeLists.txt
# Add gclados library
add_library(gclados STATIC IMPORTED)
set_target_properties(gclados PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libgclados.a)
