#!/bin/bash

# Detect OS and set executable name
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    # Windows (Git Bash)
    EXECUTABLE="./build/Debug/MarketDAQ.exe"
    if [ ! -f "$EXECUTABLE" ]; then
        EXECUTABLE="./build/Release/MarketDAQ.exe"
    fi
else
    # Linux/Unix
    EXECUTABLE="./build/MarketDAQ"
fi

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE"
    echo "Please build the project first using build.sh"
    exit 1
fi

# Run the executable
echo "Running MarketDAQ..."
"$EXECUTABLE" "$@"