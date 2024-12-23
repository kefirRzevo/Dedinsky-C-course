#ifndef LEXER_H
#define LEXER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

typedef enum {
#define LINKABLE(X) X
#define UNLINKABLE(X) X
#define KEYWORD(name, keyword, ident) name = keyword,
#include "../src/KEYWORDS"
#undef LINKABLE
#undef UNLINKABLE
#undef KEYWORD
} token_keyword;

typedef enum {
  KEYWORD = 0,
  IDENT = 1,
  NUMBER = 2,
} token_type;

typedef union {
  char *ident;
  double number;
  int keyword;
} token_value;

typedef struct {
  token_value value;
  size_t line;
  token_type type;
} token;

token *tokenize(const char *file_path, array *idents, array *tokens);

#endif