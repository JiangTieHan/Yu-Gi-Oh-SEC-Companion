#!/bin/bash

# Set build variables
SRC_DIR="src"
HEADER_DIR="header"
OUTPUT_FILE="program"

# Find all .cpp files in src/ excluding unit test files
SRC_FILES=$(find $SRC_DIR -name "*.cpp" ! -name "*Test.cpp")

# Compilation command
g++ -std=c++17 -I$HEADER_DIR -I$SRC_DIR $SRC_FILES -o $OUTPUT_FILE

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running program..."
    ./$OUTPUT_FILE
else
    echo "Compilation failed."
    exit 1
fi
