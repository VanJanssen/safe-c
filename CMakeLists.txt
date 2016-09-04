cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project ("Safe C" C)

add_library(safe-c safe-memory.c)
