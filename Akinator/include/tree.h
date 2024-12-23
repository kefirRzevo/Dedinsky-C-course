#ifndef TREE_H
#define TREE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SPECIFICATOR "s"
typedef char *data_t;

struct node {
  data_t data;
  struct node *left;
  struct node *right;
};

typedef struct node node;

typedef struct {
  size_t size;
  node *root;
} tree;

void tree_ctor(tree **p_tree);

void tree_print(tree *p_tree, FILE *datafile);

void tree_dtor(tree *p_tree);

void tree_dump(tree *p_tree);

#endif
