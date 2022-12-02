add_library(aes STATIC aes.c)

target_include_directories(aes PUBLIC "${PROJECT_SOURCE_DIR}/include/aes")
