#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

/*74 (EX_IOERR from <sysexits.h>) → File I/O error (e.g., cannot open/read a
 * file).*/
/*65 → Compilation error (e.g., syntax error in the source code).*/
/*70 (EX_SOFTWARE) → Runtime error (e.g., division by zero, null pointer
 * dereference).*/
/*64 (EX_USAGE) → Incorrect command-line usage (e.g., wrong number of
 * arguments).*/

static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }
  // NOTE:  Without '\0', functions like printf(), strlen(), and strcpy() may
  // read past the allocated buffer, leading to undefined behavior or crashes.
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

static void runFile(const char *path) {
  char *source = readFile(path);
  printf("source -- \n%s \n", source);
  Lexer lexer = initLexer(source);
  // parser parser = create_parser(&lexer);

  parse_source(source);

  free(source);
  // parse source
  /*InterpretResult result = interpret(source);*/
  /*free(source);*/
  /**/
  /*if (result == INTERPRET_COMPILE_ERROR)*/
  /*  exit(65);*/
  /*if (result == INTERPRET_RUNTIME_ERROR)*/
  /*  exit(70);*/
}

int main(int argc, const char *argv[]) {

  if (argc == 1) {
    // TODO create VM and run bytecode version?
    /*repl();*/
  } else if (argc == 2) {
    runFile(argv[1]);

  } else {
    fprintf(stderr, "Usage: pebble [path]\n");
    exit(64);
  }

  printf("Hellow Pebble");
}
