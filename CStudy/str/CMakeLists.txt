# CMake minimum version
cmake_minimum_required(VERSION 3.5)

# Project name
project(StrProject)

# Include directories
include_directories(../include)

# Source files
set(SOURCES
    src/str.c
    src/str.h
    main.c
)

# Add an executable
add_executable(Str ${SOURCES})