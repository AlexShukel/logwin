file(GLOB SRC_FILES *.test.c)

find_program(GCLADOS "gclados")
if(GCLADOS)
    add_custom_command(
            OUTPUT ./entry.c
            COMMAND gclados generate ./*.test.c --output ./entry.c
            DEPENDS ${SRC_FILES}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

# Add gclados library
add_library(gclados STATIC IMPORTED)
set_target_properties(gclados PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libgclados.a)
