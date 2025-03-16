#include "lexer.h"
#include "stdbool.h"
#include <stdio.h>

char *tokenTypeToString(Token token) {
  switch (token.type) {
  case TOKEN_INTEGER:
    return "INTEGER";
  case TOKEN_STRING:
    return "STRING";
  case TOKEN_BOOLEAN:
    return "BOOLEAN";
  case TOKEN_EOF:
    return "EOF";
    break;
  case TOKEN_EQ:
  case TOKEN_NOT_EQ:
  case TOKEN_ASSIGN:
  case TOKEN_PLUS:
    return "+";
  case TOKEN_MINUS:
  case TOKEN_BANG:
  case TOKEN_ASTERISK:
  case TOKEN_SLASH:
  case TOKEN_LT:
  case TOKEN_GT:
    return "";
    break;
  case TOKEN_ILLEGAL:
    return "illegal token!";
    break;
  }
}

// Consume and return character
char advance(Lexer *lexer) {
  lexer->current++;
  return lexer->current[-1];
}

bool isAtEnd(Lexer *lexer) { return *lexer->current == '\0'; }

char peek(Lexer *lexer) { return lexer->current[0]; }

static void skipWhitespace(Lexer *lexer) {
  for (;;) {
    char c = peek(lexer);
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance(lexer);
      break;
    case '\n':
      lexer->line++;
      advance(lexer);
      break;
    default:
      return;
    }
  }
}
Token makeToken(Lexer *lexer, TokenType type) {
  Token token = {0};
  token.offset = lexer->start - lexer->startOfSource;
  token.length = lexer->current - lexer->start;
  token.line = lexer->line;
  token.type = type;
  return token;
}

Token makeErrorToken(Lexer *lexer) {
  Token token = {0};
  token.offset = lexer->start - lexer->startOfSource;
  token.length = lexer->current - lexer->start;
  token.line = lexer->line;
  token.type = TOKEN_ILLEGAL;
  return token;
}

Lexer initLexer(const char *source) {
  Lexer lexer = {0};
  lexer.startOfSource = source;
  lexer.start = source;
  lexer.current = source;
  lexer.line = 0;
  return lexer;
}

Token nextToken(Lexer *lexer) {

  // skip whitespaces, new lines
  skipWhitespace(lexer);

  // set start to current after each token
  lexer->start = lexer->current;

  if (isAtEnd(lexer)) {
    return makeToken(lexer, TOKEN_EOF);
  }
  char c = advance(lexer);
  switch (c) {
  case '+':
    return makeToken(lexer, TOKEN_PLUS);
    break;
  }
  return makeErrorToken(lexer);
}
