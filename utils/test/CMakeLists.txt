include(gclados)

add_executable(utilsTests ${SRC_FILES} entry.c)

include_directories(utilsTests "${PROJECT_SOURCE_DIR}/include/gclados")
target_include_directories(utilsTests PUBLIC "${PROJECT_SOURCE_DIR}/include/utils")

target_link_libraries(utilsTests utils gclados)

add_test(NAME UTILS COMMAND utilsTests)
