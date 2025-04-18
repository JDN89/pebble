#include "lexer.h"
#include "stdbool.h"
#include <string.h>

static Token makeToken(Lexer *lexer, TokenType type);

char *tokenTypeToString(TokenType type) {
  switch (type) {
  case TOKEN_INTEGER:
    return "TOKEN_INTEGER";
  case TOKEN_TYPE_DECLARATION:
    return "TOKEN_TYPE_DECLARATION";
  case TOKEN_EOF:
    return "TOKEN_EOF";
  case TOKEN_ASSIGN:
    return "TOKEN_ASSIGN";
  case TOKEN_PLUS:
    return "TOKEN_PLUS";
  case TOKEN_ILLEGAL:
    return "TOKEN_ILLEGAL";
  case TOKEN_IDENTIFIER:
    return "TOKEN_IDENTIFIER";
  case TOKEN_COLON:
    return "TOKEN_COLON";
  case TOKEN_CONST_DECLARATION:
    return "TOKEN_CONST_DECLARATION";
  case TOKEN_MUT_DECLARATION:
    return "TOKEN_MUT_DECLARATION";
  case TOKEN_KEYWORD:
    return "TOKEN_KEYWORD";
  case TOKEN_MINUS:
    return "TOKEN_MINUS";
  case TOKEN_ASTERISK:
    return "TOKEN_ASTERISK";
  case TOKEN_SLASH:
    return "TOKEN_SLASH";
    break;
  }
  return "UNKNOW TOKEN";
}

// Consume and return character
char advance(Lexer *lexer) {
  lexer->current++;
  return lexer->current[-1];
}

char peek(Lexer *lexer) { return lexer->current[0]; }

bool isAtEnd(Lexer *lexer) { return *lexer->current == '\0'; }

// TODO: this method will get called a lot. See there is any wiggle room for
// optimization Look at lua or tinyCC compiler for exmaples or inspiration
bool isChar(char c) {
  return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

// TODO: this method will get called a lot. See there is any wiggle room for
// optimization Look at lua or tinyCC compiler for exmaples or inspiration
bool isNumber(char c) { return ('0' <= c && c <= '9'); }

// TODO: this method will get called a lot. See there is any wiggle room for
// optimization
Token checkKeyword(Lexer *lexer, TokenType type, const char *keyword) {
  if (memcmp(lexer->start, keyword, lexer->current - lexer->start) == 0) {
    return makeToken(lexer, type);
  } else {
    return makeToken(lexer, TOKEN_IDENTIFIER);
  }
}

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
  case '-':
    return makeToken(lexer, TOKEN_MINUS);
    break;
  case '*':
    return makeToken(lexer, TOKEN_ASTERISK);
    break;
  case '/':
    return makeToken(lexer, TOKEN_SLASH);
    break;
    // BUG: this fails in test why? returns token TOKEN_COLON
  case ':':
    switch (advance(lexer)) {
    case ':':
      return makeToken(lexer, TOKEN_CONST_DECLARATION);
      break;
    case '=':
      return makeToken(lexer, TOKEN_MUT_DECLARATION);
      break;
    default:
      return makeToken(lexer, TOKEN_COLON);
    }
    return makeToken(lexer, TOKEN_COLON);
    break;
  case '=':
    return makeToken(lexer, TOKEN_ASSIGN);
    break;
  default:
    if (isChar(c)) {
      while (isChar(peek(lexer))) {
        advance(lexer);
      }
      switch (lexer->start[0]) {
      case 'i':
        return checkKeyword(lexer, TOKEN_TYPE_DECLARATION, "int");
        break;
      default:
        return makeToken(lexer, TOKEN_IDENTIFIER);
        break;
      }
    }
    if (isNumber(c)) {
      while (isNumber(peek(lexer))) {
        advance(lexer);
      }
      // NOTE: we switch on the start of the current token to see if it's an
      // identifer or a keyword
      return makeToken(lexer, TOKEN_INTEGER);
    }
  }
  return makeErrorToken(lexer);
}
