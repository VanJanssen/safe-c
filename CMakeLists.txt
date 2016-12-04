cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project ("Safe C" C)

if(${CMAKE_C_COMPILER_ID} STREQUAL GNU OR
    ${CMAKE_C_COMPILER_ID} STREQUAL Clang)
    # -Wstrict-prototypes can't be used because it causes errors in Criterion
    set(warnings "-Wall -Wextra -Werror -Wmissing-include-dirs -Wswitch-default -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wmissing-prototypes -Wnested-externs")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    set(warnings "/W4 /WX /wd4996")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}")


include_directories(include)

add_library(safe-c include/safe-c/safe_memory.h
                   include/safe-c/safe_string.h
                   src/safe_memory.c
                   src/safe_string.c)

# ----- Check for dependencies -----
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib)

if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)
    include_directories(dependencies/include)
endif()

# Criterion is the unit testing framework and is required for building the tests.
find_library(CRITERION criterion)
if(CRITERION)
    message(STATUS "Criterion - found")
    enable_testing()
    add_subdirectory(tests)
else(CRITERION)
    message(STATUS "Criterion - not found")
endif()
