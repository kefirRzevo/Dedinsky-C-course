#ifndef AKINATOR_H
#define AKINATOR_H

#include "parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef size_t error_t;

void akinator(char *textfile_path);

typedef enum {
  OPEN_BRACKET_NOT_FOUND = 1 << 0,
} errors;

typedef enum {
  GUESS = 1,
  COMPARE = 2,
  DEFINE = 3,
  SAVE = 4,
  EXIT = 5,
  YOU_PUT_HUYNYA = 6,
} mode;

#endif
