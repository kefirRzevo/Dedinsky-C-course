#ifndef PROCESSOR_PARSER_H
#define PROCESSOR_PARSER_H

static const double EPSILON = 0.000001;

#include "lexer.h"

typedef enum {
  is_register = 1,
  is_number = 2,
  is_ram_register = 3,
  is_char = 4,
  is_nothing = 5,
  is_label = 6,
} type_of_argument;

typedef struct {
  char key;
  type_of_argument argument_type;
  double argument;
} Command;

typedef struct {
  char *label;
  int to;
  int from;
} labeled_cmd;

array *create_binfile(const char *binfile_path, array *tokens);

#endif // PROCESSOR_PARSER_H
