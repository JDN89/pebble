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
    gcc -Wall -Wextra -pedantic  *.c src/*. -o pebble && ./pebble
fi

if [[ $1 == "test_lexer" ]]; then
    rm -f test_lexer  # Remove old executable if it exists
    gcc -Wall -Wextra -pedantic  main.c src/test_lexer.c -o test_lexer && ./test_lexer
fi
