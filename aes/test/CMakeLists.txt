file(GLOB SRC_FILES *.test.c)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/entry.c
        COMMAND gclados generate ${CMAKE_CURRENT_SOURCE_DIR}/*.test.c --output ${CMAKE_CURRENT_SOURCE_DIR}/entry.c
        DEPENDS ${SRC_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add gclados library
add_library(gclados STATIC IMPORTED)
set_target_properties(gclados PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libgclados.a)

add_executable(aesTests ${SRC_FILES} entry.c)

include_directories(aesTests "${PROJECT_SOURCE_DIR}/include/gclados")
target_include_directories(aesTests PUBLIC "${PROJECT_SOURCE_DIR}/include/aes")

target_link_libraries(aesTests aes gclados)

add_test(NAME AES_TESTS COMMAND aesTests)

target_include_directories(aesTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

# utils
target_link_libraries(aesTests utils)
