function(add_unit_test test_name)
    add_executable(${test_name} ${test_name}.c)
    target_link_libraries(${test_name} safe-c criterion)
    add_test(${test_name} ${test_name})
endfunction(add_unit_test)

add_subdirectory(safe_memory)
