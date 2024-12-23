#ifndef TREE_H
#define TREE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#define OPER_SPEC "s"
#define VAR_SPEC "c"
#define NUM_SPEC "lg"

typedef enum {
  // binary
  OPER_ADD = 0X2B,
  OPER_SUB = 0X2D,
  OPER_MUL = 0X2A,
  OPER_DIV = 0X2F,
  OPER_POW = 0X5E,

  // unary
  OPER_LN = 0X6C6E,
  OPER_SIN = 0X73691D,
  OPER_COS = 0X636F10,
  OPER_SH = 0X7368,
  OPER_CH = 0X6368,

  // deriviation
  OPER_DDX = 0x64,
} OperType;

typedef enum {
  NUM = 1,
  VAR = 2,
  OPER = 3,
} NodeType;

typedef union {
  double number;
  char variable;
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
  hash_t hash;
} Tree;

Node *node_delete(Node *tree_node);

Node *node_cpy(Node *p_node);

Tree *tree_ctor(Tree **p_tree);

Tree *tree_dtor(Tree *p_tree);

Tree *tree_viz_dump(Tree *p_tree);

Node *tree_compare(Node *n1, Node *n2);

size_t count_tree_size(Node *p_node);

hash_t count_hash(Node *p_node);

Node *new_oper_node(OperType type, Node *lnode, Node *rnode);

Node *new_var_node(char var);

Node *new_num_node(double num);

#endif
