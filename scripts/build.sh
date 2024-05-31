#!/bin/bash

# Build the project

# verify that this is running in the project root
if [ ! -f "project.yml" ]; then
  echo "Error: must be run from the project root."
  echo "Note: this script is looking for the project.yml file to determine what directory it's called from."
  exit 1
fi

#if the build directory does not exist, create it
if [ ! -d "build" ]; then
  mkdir build
fi

# Run cmake to generate the build files
cd build
cmake ..

# Run make to build the project
make
