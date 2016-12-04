function(add_unit_test test_name)
    add_executable(${test_name} ${test_name}.c)
    target_link_libraries(${test_name} safe-c criterion)
    add_test(${test_name} ${test_name})
endfunction(add_unit_test)

# These warnings are triggered by Criterion when building the unit tests. These warnings
# will be disabled untill they are fixed in Criterion.
if(${CMAKE_C_COMPILER_ID} STREQUAL GNU OR
    ${CMAKE_C_COMPILER_ID} STREQUAL Clang)
    # -Wstrict-prototypes
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4255 /wd4464 /wd4820")
endif()

add_subdirectory(safe_memory)
