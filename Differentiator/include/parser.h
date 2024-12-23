#ifndef PARSER_H
#define PARSER_H
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Tree *parse(Tree *p_tree, char *equation_file_path);

#endif
