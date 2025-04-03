CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -g  # Debug flags with debug symbols
CFLAGS_RELEASE = -Wall -Wextra -O2  # Release flags with optimization (-O2)

SOURCES = src/main.c src/lexer.c src/parser.c
OBJECTS = $(SOURCES:src/%.c=build/%.o)  # Fixed the object file path here
EXECUTABLE = build/pebble

# Test sources (assuming you have test_lexer.c)
TEST_SOURCES = test/test_lexer.c src/lexer.c
TEST_OBJECTS = $(TEST_SOURCES:src/%.c=build/%.o)  # Fixed this as well
TEST_EXECUTABLE = build/test_lexer

# Ensure the build directory exists before compiling
$(shell mkdir -p build)

# By default, use debug flags unless explicitly set to release
CFLAGS = $(CFLAGS_DEBUG)

# Default target to build the main executable and run it (in debug mode by default)
all: $(EXECUTABLE)
	./$(EXECUTABLE)  # Executes the main program after it's built

# Build the main executable (can be debug or release based on CFLAGS)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Build the test lexer executable
test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(TEST_EXECUTABLE) $(TEST_OBJECTS)
	./$(TEST_EXECUTABLE) # Executes the test after building

# Pattern rule to compile .c files into .o objects and put them in the build directory
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up generated files
clean:
	rm -rf build

# Run the executable after building it (if needed, this can be a separate target you want to run)
run: $(EXECUTABLE)
	./$(EXECUTABLE)  # Executes the main program (or any other target you want to run)

# Target for release build (uses release flags)
release: CFLAGS = $(CFLAGS_RELEASE)
release: $(EXECUTABLE)
	./$(EXECUTABLE)  # Runs the release version
