# Add the minimum CMake version required
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(serial_tool)

# Set the output directory for the build executables.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the subdirectories
add_subdirectory(src)
