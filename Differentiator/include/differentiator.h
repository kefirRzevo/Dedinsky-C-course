#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "optimizer.h"
#include "parser.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Tree *differentiate(Tree *p_tree, char variable);

FILE *tex_open();
void tex_tree(Tree *p_tree, bool phrase);
void tex_msg(const char message[]);

#endif
