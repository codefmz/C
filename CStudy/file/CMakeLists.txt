# CMake minimum version
cmake_minimum_required(VERSION 3.5)

# Project name
project(StrProject)

# Include directories
include_directories(../include)

# Source files
set(SOURCES
    src/file.c
    src/file.h
    main.c
)

# Add an executable
add_executable(File ${SOURCES})