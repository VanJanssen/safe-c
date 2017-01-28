cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project ("elegan-c" C)

# ============================ Enable code coverage ============================
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/.cmake/codecov/cmake" ${CMAKE_MODULE_PATH})
find_package(codecov)


# ============================ Set compiler options ============================
if(${CMAKE_C_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()

if(${CMAKE_C_COMPILER_ID} STREQUAL GNU OR
    ${CMAKE_C_COMPILER_ID} STREQUAL Clang)
    # -Wstrict-prototypes can't be used because it causes errors in Criterion
    set(warnings "-Wall -Wextra -Werror -Wmissing-include-dirs -Wswitch-default -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wmissing-prototypes -Wnested-externs")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    # For MSVC we use the /Wall option. This option enables various usefull warnings,
    # but also notification-like warnings that cause the build to fail when using /WX,
    # so we disable those.
    set(warnings "/Wall /WX")

    # Warning C4710: 'function' not inlined
    # The inline keyword is used as a hint for the compiler, this warning indicates
    # that inlining didn't happen. Can be triggered by standard functions like `fprintf()`
    set(warnings "${warnings} /wd4710")

    # Warning C4711: 'function' selected for inline expansion
    # The compiler performed inlining on the given function, although it was not
    # marked for inlining, as an optimization. This warning is informational.
    set(warnings "${warnings} /wd4711")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}")




# ========================== Specify library sources ===========================
include_directories(include)

add_library(elegan-c
    include/elegan-c/common.h
    include/elegan-c/memory.h
    include/elegan-c/string.h
    src/common.c
    src/memory.c
)

add_coverage(elegan-c)

# Evaluate coverage here, so only the code of the main library is included in
# the coverage report
coverage_evaluate()


# ========================= Enable testing if possible =========================
set(dependencies_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)
set(dependencies_lib_dir ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib)

if(IS_DIRECTORY ${dependencies_include_dir})
    include_directories(dependencies/include)
endif()

if(IS_DIRECTORY ${dependencies_lib_dir})
    link_directories(${dependencies_lib_dir})
endif()

find_library(CRITERION criterion)

if(CRITERION)
    message(STATUS "Criterion - found")
    enable_testing()
    add_subdirectory(tests)
else(CRITERION)
    message(STATUS "Criterion - not found")
endif()
