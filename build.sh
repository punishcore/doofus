#!/bin/bash

set -e

echo "Cleaning old build..."
rm -rf build

echo "Creating build directory..."
mkdir build
cd build

echo "Running CMake..."
cmake ..

echo "Building project..."
cmake --build .

echo "Running game..."
./doofus