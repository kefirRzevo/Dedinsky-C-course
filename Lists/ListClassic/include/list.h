#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int item_t;

#define SPECIFICATOR "d"
#define comp(a, b) a == b

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

void list_insert_tail(list *const p_list, const item_t item);

void list_insert_head(list *const p_list, const item_t item);

void list_delete_tail(list *const p_list, item_t *p_item);

void list_delete_head(list *const p_list, item_t *p_item);

void list_delete_node(list *const p_list, node *const p_node, item_t *p_item);

node *list_data_search(list *const p_list, const item_t item);

#endif
