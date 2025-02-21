#!/bin/bash

# Set build variables
SRC_DIR="src"
TEST_DIR="test"
HEADER_DIR="header"
OUTPUT_FILE="testRunner"

# Check if a specific test file is provided
if [ -z "$1" ]; then
    echo "No test specified. Running all tests..."
    TEST_FILES=$(ls $TEST_DIR/*.cpp)
else
    TEST_FILES="$TEST_DIR/$1"
    if [ ! -f "$TEST_FILES" ]; then
        echo "Error: Test file $1 not found in $TEST_DIR."
        exit 1
    fi
fi

# Compilation command
g++ -std=c++17 -I$HEADER_DIR -I$SRC_DIR -I$TEST_DIR \
    $SRC_DIR/*.cpp $TEST_FILES \
    -o $OUTPUT_FILE -lCppUTest -lCppUTestExt

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running tests..."
    ./$OUTPUT_FILE
    # Remove testRunner after execution
    rm -f $OUTPUT_FILE
else
    echo "Compilation failed."
    exit 1
fi
