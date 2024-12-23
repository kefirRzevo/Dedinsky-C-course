#ifndef LEXER_H
#define LEXER_H

#include "array.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  CMD = 0,
  REG = 1,
  NUM = 2,
  KW = 3,
  CH = 4,
  LAB = 5,
} token_type;

typedef union {
  char command;
  char reg;
  double number;
  char keyword;
  char ch;
  char *label;
} token_value;

typedef struct {
  token_value value;
  size_t line;
  token_type type;
} token;

token *tokenize(const char *file_path, array *idents, array *tokens);

#endif
