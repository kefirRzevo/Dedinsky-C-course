#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include "array.h"
#include "tree.h"

typedef struct {
  array scoop_levels;
  array functions;
  int shift;
} sym_table;

typedef struct {
  char *name;
  size_t size;
  int adress;
  bool is_const;
  Node *declared;
} var;

typedef struct {
  char *name;
  Node *declared;
  size_t n_params;
} func;

sym_table *delete_sym_table(sym_table *table);
sym_table *create_sym_table(sym_table *table, int init_shift);
sym_table *dump_sym_table(sym_table *table);

size_t count_shift_size(sym_table *table);
array *create_scoop_level(sym_table *table);
array *create_function_list(sym_table *table);
array *delete_scoop_level(sym_table *table);

func *add_function(sym_table *table, Node *func_node);
func *find_function(sym_table *table, Node *func_node);
var *find_variable(sym_table *table, Node *var_node);
var *add_variable(sym_table *table, Node *var_node);

#endif
