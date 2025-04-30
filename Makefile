# Compiler and flags
CC = clang
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g

# Executables
EXECUTABLE = build/pebble
TEST_EXECUTABLES = build/test_lexer build/test_arena

# Make sure build/ exists
build:
	mkdir -p build

# Default build target
all: $(EXECUTABLE)

# Build main program
$(EXECUTABLE): build
	$(CC) $(CFLAGS_DEBUG) -o build/pebble src/main.c src/lexer.c src/parser.c src/arena.c src/program.c 

# Build tests
build/test_lexer: build
	$(CC) $(CFLAGS_DEBUG) -o build/test_lexer test/test_lexer.c src/lexer.c 

build/test_arena: build
	$(CC) $(CFLAGS_DEBUG) -o build/test_arena test/test_arena.c src/arena.c src/program.c

# Run tests
test: $(TEST_EXECUTABLES)
	./build/test_lexer
	./build/test_value
	./build/test_arena

test_lexer: $(TEST_EXECUTABLES)
	./build/test_lexer
	
test_arena: $(TEST_EXECUTABLES)
	./build/test_arena
# Run main program
run: $(EXECUTABLE)
	./build/pebble

# Clean everything
clean:
	rm -rf build
