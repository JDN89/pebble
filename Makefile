CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -g  # Debug flags with debug symbols
CFLAGS_RELEASE = -Wall -Wextra -O2  # Release flags with optimization (-O2)

# Source files
SOURCES = src/main.c src/lexer.c src/parser.c
OBJECTS = $(SOURCES:src/%.c=build/%.o)
EXECUTABLE = build/pebble

# Test source files
TEST_SOURCES = test/test_lexer.c test/test_value.c src/lexer.c src/parser.c src/value.c
TEST_OBJECTS = $(patsubst src/%.c,build/%.o,$(filter src/%.c,$(TEST_SOURCES))) \
               $(patsubst test/%.c,build/%.o,$(filter test/%.c,$(TEST_SOURCES)))

TEST_EXECUTABLES = build/test_lexer build/test_value

# Ensure build directory exists
$(shell mkdir -p build)

# Default target
all: $(EXECUTABLE)

# Main program build
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Test build and run
test: $(TEST_EXECUTABLES)
	@./build/test_lexer
	@./build/test_value

build/test_lexer: build/test_lexer.o build/lexer.o build/parser.o
	$(CC) $(CFLAGS) -o $@ $^

build/test_value: build/test_value.o build/value.o
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rules
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/%.o: test/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -rf build

# Run main program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Release build
release: CFLAGS = -O2 -Wall
release: $(EXECUTABLE)
	./$(EXECUTABLE)
