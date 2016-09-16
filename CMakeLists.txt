cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project ("Safe C" C)

if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror -Wmissing-include-dirs -Wswitch-default -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Wdouble-promotion -Wtrampolines -Wlogical-op")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
    set(warnings "/W4 /WX /wd4996")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}")


include_directories(include)

add_library(safe-c include/safe-c/safe_memory.h
                   include/safe-c/safe_string.h
                   src/safe_memory.c
                   src/safe_string.c)

find_library(CRITERION criterion)

if(CRITERION)
    add_executable(unit_tests tests/safe_memory/safe_malloc.c)
    target_link_libraries(unit_tests safe-c criterion)
    
    enable_testing()
    add_test(unit_tests unit_tests)
endif()
