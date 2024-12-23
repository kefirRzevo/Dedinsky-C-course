#ifndef COMPILER_H
#define COMPILER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "symtable.h"
#include "tree.h"

Tree *compile_tree(const char *filepath, Tree *p_tree);

#endif
