#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPECIFICATOR "zu"

typedef struct {
  char mas[16];
  size_t size;
} item_t;

struct node {
  item_t data;
  struct node *next;
  struct node *prev;
};

typedef struct node node;

typedef struct {
  node *head;
  node *tail;
  size_t size;
} list;

void list_ctor(list *const p_list);

void list_dtor(list *const p_list);

void list_dump(const list *const p_list);

void list_insert_tail(list *const p_list, const item_t item);

void list_insert_head(list *const p_list, const item_t item);

void list_delete_tail(list *const p_list, item_t *p_item);

void list_delete_head(list *const p_list, item_t *p_item);

void list_delete_node(list *const p_list, node *const p_node);

node *list_data_search(list *const p_list, const item_t item);

FILE *open_dot_txt(const char *const dotfile_path);

void print_nodes(const list *const p_list, FILE *const dotfile);

void close_dot_txt(FILE *const dotfile);

#endif
