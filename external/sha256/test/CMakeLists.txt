include(gclados)

add_executable(sha256Tests ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/entry.c")

include_directories(sha256Tests "${PROJECT_SOURCE_DIR}/include/gclados")
target_include_directories(sha256Tests PUBLIC "${PROJECT_SOURCE_DIR}/include/sha256")

target_link_libraries(sha256Tests sha256 gclados)

add_test(NAME SHA256 COMMAND sha256Tests)
