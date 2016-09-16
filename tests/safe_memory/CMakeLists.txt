add_executable(safe_malloc safe_malloc.c)
target_link_libraries(safe_malloc safe-c criterion)
add_test(safe_malloc safe_malloc)