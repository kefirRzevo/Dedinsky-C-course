#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

static const double EPS = 1E-05;
static const double E = 2.71828182845;
static const double P = 3.14159265358;

Tree *optimize(Tree *p_tree);

#endif
