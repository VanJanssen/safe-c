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
    if (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
        # For now, assume that criterion.lib is located in this folder on Windows.
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/criterion/build/Release/)
        include_directories(dependencies/criterion/include)
    endif()

    enable_testing()
    add_subdirectory(tests)
endif()
