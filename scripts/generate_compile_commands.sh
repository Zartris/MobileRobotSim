#!/bin/bash

# This script generates a compile_commands.json file for clangd to use.
# It runs CMake in the build directory with the appropriate flags to generate
# the compile_commands.json file, then copies it to the project root.

set -e  # Exit on error

# Create build directory if it doesn't exist
mkdir -p build

# Go to build directory
cd build

# Run CMake with compile commands generation enabled
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Copy compile_commands.json to the project root
cp compile_commands.json ..

echo "Compilation database generated and copied to project root."
echo "clangd should now work properly with the project."
