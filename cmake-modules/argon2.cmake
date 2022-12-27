add_library(argon2 STATIC IMPORTED)
set_target_properties(argon2 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libargon2.a)
