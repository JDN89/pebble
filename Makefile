# Compiler and flags
CC = clang
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g

# Executables
EXECUTABLE = build/pebble
TEST_EXECUTABLES = build/test_lexer build/test_value

# Make sure build/ exists
build:
	mkdir -p build

# Default build target
all: $(EXECUTABLE)

# Build main program
$(EXECUTABLE): build
	$(CC) $(CFLAGS_DEBUG) -o build/pebble src/main.c src/lexer.c src/parser.c

# Build tests
build/test_lexer: build
	$(CC) $(CFLAGS_DEBUG) -o build/test_lexer test/test_lexer.c src/lexer.c src/parser.c

build/test_value: build
	$(CC) $(CFLAGS_DEBUG) -o build/test_value test/test_value.c src/value.c

# Run tests
test: $(TEST_EXECUTABLES)
	./build/test_lexer
	./build/test_value

test_lexer: $(TEST_EXECUTABLES)
	./build/test_lexer
	
# Run main program
run: $(EXECUTABLE)
	./build/pebble

# Clean everything
clean:
	rm -rf build
