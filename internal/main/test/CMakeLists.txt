include(gclados)

add_executable(mainTests ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/entry.c")

include_directories(mainTests "${PROJECT_SOURCE_DIR}/include/gclados")
target_include_directories(mainTests PUBLIC "${PROJECT_SOURCE_DIR}/include/main")
target_include_directories(mainTests PUBLIC "../src")

target_link_libraries(mainTests main gclados)

add_test(NAME MAIN COMMAND mainTests)
