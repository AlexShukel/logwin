include(gclados)

add_executable(aesTests ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/entry.c")

include_directories(aesTests "${PROJECT_SOURCE_DIR}/include/gclados")
target_include_directories(aesTests PUBLIC "${PROJECT_SOURCE_DIR}/include/aes")

target_link_libraries(aesTests aes gclados)

add_test(NAME AES_TESTS COMMAND aesTests)

target_include_directories(aesTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

# utils
target_link_libraries(aesTests utils)
