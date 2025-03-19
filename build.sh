#!/bin/bash

set -e  # Exit on error

# Remove old executables
rm -f pebble test_lexer

# Compile main program and test files when you don't give arguments
# pebble
gcc -Wall -Wextra -pedantic -g main.c src/*.c -o pebble

# test_lexer
gcc -Wall -Wextra -pedantic -g src/lexer.c test/test_lexer.c -o test_lexer

# Check CLI argument
case "$1" in
    run)
        ./pebble "${2:-}"
        ;;
    test_lexer)
	./test_lexer
        ;;
    *)
        echo "Usage: $0 {run|test_lexer}"
        exit 1
        ;;
esac
