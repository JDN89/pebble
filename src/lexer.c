#include "lexer.h"
#include "stdbool.h"

char *tokenTypeToString(TokenType type) {
  switch (type) {
  case TOKEN_INTEGER:
    return "INTEGER";
  case TOKEN_TYPE_DECLARATION:
    return "TYPE_DECLARATION";
  case TOKEN_EOF:
    return "EOF";
  case TOKEN_ASSIGN:
    return "=";
  case TOKEN_PLUS:
    return "+";
  case TOKEN_ILLEGAL:
    return "illegal token!";
  case TOKEN_IDENTIFIER:
    return "TOKEN_IDENTIFIER";
  case TOKEN_COLON:
    return ":";
  case TOKEN_CONST_DECLARATION:
    return "::";
  case TOKEN_MUT_DECLARATION:
    return ":=";
  }
  return "UNKNOW TOKEN";
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
