#!/bin/bash

# Make sure the script is executable
# excute in cli: chmod +x build.sh
#
# run script
# ./build.sh run

# Compile command
 rm -f pebble  # Remove old executable if it exists
 gcc -Wall -Wextra -pedantic -g *.c src/*.c -o pebble

# Check CLI argument
if [[ $1 == "run" ]]; then
    rm -f pebble  # Remove old executable if it exists
    gcc -Wall -Wextra -pedantic -g *.c src/*.c -o pebble

    if [[ $? -eq 0 ]]; then  # Check if compilation was successful
        if [[ -n $2 ]]; then
            ./pebble "$2"
        else
            ./pebble
        fi
    else
        echo "Compilation failed."
        exit 1
    fi
fi

if [[ $1 == "test_lexer" ]]; then
    rm -f test_lexer  # Remove old executable if it exists
    gcc -Wall -Wextra -pedantic  main.c src/test_lexer.c -o test_lexer && ./test_lexer
fi
