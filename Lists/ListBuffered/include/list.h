#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef int item_t;
#define SPECIFICATOR "d"

static const int TRASH_NEXT = -117;
static const int TRASH_PREV = -1;

typedef struct {
  int prev;
  int next;
} node;

typedef struct {
  item_t *data;
  node *nodes;

  size_t capacity;
  size_t size;

  size_t free_pos;
  bool linerazed;
} list;

void list_ctor(list *const p_list);

void list_dtor(list *const p_list);

void list_insert(list *const p_list, const size_t item_pos, const item_t item);

item_t list_delete(list *const p_list, size_t const item_pos);

size_t find_phys_indx(list *const p_list, size_t const logic_indx);

void list_sort(list *const p_list);

void quick_list_sort(list *const p_list);

#endif
