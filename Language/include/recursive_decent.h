#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lexer.h"
#include "tree.h"

Tree *create_tree(array *tokens);

#endif
