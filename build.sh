#!/bin/bash

# Make sure the script is executable
# excute in cli: chmod +x build.sh
#
# run script
# ./build.sh run

# Compile command
gcc -Wall -Wextra -pedantic *.c -o pebble 

# Check CLI argument
if [[ $1 == "run" ]]; then
    rm -f pebble  # Remove old executable if it exists
    gcc -Wall -Wextra -pedantic  *.c -o pebble && ./pebble
fi
