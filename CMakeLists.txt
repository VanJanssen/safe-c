cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project ("Safe C")

add_library(safe-c safe-memory.c)
