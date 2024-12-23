#ifndef TREE_H
#define TREE_H

#include "array.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OPER_SPEC "s"
#define ID_SPEC "s"
#define NUM_SPEC "lg"

static const double EPSILON = 0.001;

typedef enum {
#define OPER(name, keyword, ident) name = keyword,
#include "../src/STANDARD_TREE"
#undef OPER
} OperType;

typedef enum {
  NUM = 1,
  ID = 2,
  OPER = 3,
} NodeType;

typedef union {
  double number;
  char *ident;
  OperType oper_type;
} NodeValue;

struct Node {
  NodeType Type;
  NodeValue Value;
  struct Node *Left;
  struct Node *Right;
};

typedef struct Node Node;

typedef struct {
  size_t size;
  Node *root;
} Tree;

size_t count_tree_size(Node *p_node);
Node *node_delete(Node *p_node);
Node *node_cpy(Node *p_node);
Node *tree_compare(Node *n1, Node *n2);
void tree_visit(Node *p_node, void (*function)(Node *));
Tree *tree_ctor(Tree **p_tree);
Tree *tree_dtor(Tree *p_tree);
Tree *tree_dump(Tree *p_tree);
Tree *tree_write(Tree *p_tree, const char *filepath);
Tree *tree_read(array *idents, const char *filepath);

bool is_node_number(Node *node);
bool is_node_natural(Node *node);
char *is_node_ident(Node *node);
int is_node_opertor(Node *node, int type);

double get_node_number(Node *node);
const char *get_node_string(Node *node);

#endif
