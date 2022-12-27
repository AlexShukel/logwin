include(gclados)

add_executable(menuTests ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/entry.c")

include_directories(menuTests "${PROJECT_SOURCE_DIR}/include/gclados")
target_include_directories(menuTests PUBLIC "${PROJECT_SOURCE_DIR}/include/menu")
target_include_directories(menuTests PUBLIC "${PROJECT_SOURCE_DIR}/include/pdcurses")

target_link_libraries(menuTests menu gclados)

add_test(NAME MENU COMMAND menuTests)
