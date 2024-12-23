#include "../include/list.h"

const size_t INITIAL_CAPACITY = 10;
const size_t MAX_CAPACITY = 10000000;

size_t find_phys_indx(list *const p_list, size_t const logic_indx) {
  assert(p_list);

  if (logic_indx < 0 || logic_indx > p_list->size) {
    printf("Incorrect logic index.\n");
    return 0;
  }

  size_t phys_indx = 0;
  for (size_t i = 0; i < logic_indx; i++) {
    phys_indx = p_list->nodes[phys_indx].next;
  }
  return phys_indx;
}

static void realloc_list(list *p_list, size_t new_capacity) {
  assert(p_list);

  item_t *new_data = p_list->data;
  node *new_nodes = p_list->nodes;

  new_data = (item_t *)realloc((void *)new_data, new_capacity * sizeof(item_t));
  new_nodes = (node *)realloc((void *)new_nodes, new_capacity * sizeof(node));
  assert(new_data);
  assert(new_nodes);

  if (p_list->capacity < new_capacity) {
    for (size_t i = new_capacity / 2; i < new_capacity - 1; i++) {
      new_nodes[i].next = -i - 1;
      new_nodes[i].prev = TRASH_PREV;
    }
    p_list->free_pos = p_list->capacity;
  } else {
    p_list->free_pos = p_list->size;
  }

  new_nodes[new_capacity - 1].next = TRASH_NEXT;
  new_nodes[new_capacity - 1].prev = TRASH_PREV;

  p_list->data = new_data;
  p_list->nodes = new_nodes;
}

void list_ctor(list *const p_list) {
  assert(p_list);

  item_t *data = (item_t *)calloc(INITIAL_CAPACITY, sizeof(item_t));
  node *nodes = (node *)calloc(INITIAL_CAPACITY, sizeof(node));
  assert(data);
  assert(nodes);

  for (size_t i = 1; i < INITIAL_CAPACITY - 1; i++) {
    nodes[i].next = -i - 1;
    nodes[i].prev = -1;
  }
  nodes[INITIAL_CAPACITY - 1].next = TRASH_NEXT;
  nodes[INITIAL_CAPACITY - 1].prev = TRASH_PREV;

  p_list->size = 1;
  p_list->capacity = INITIAL_CAPACITY;
  p_list->data = data;
  p_list->nodes = nodes;
  p_list->free_pos = 1;
  p_list->linerazed = true;
}

void list_dtor(list *const p_list) {
  assert(p_list);

  item_t *data = p_list->data;
  node *nodes = p_list->nodes;

  free(data);
  free(nodes);

  p_list->size = 0;
  p_list->capacity = 0;
  p_list->free_pos = 0;
  p_list->linerazed = false;
  p_list->data = NULL;
  p_list->nodes = NULL;
}

void list_insert(list *const p_list, const size_t item_pos, const item_t item) {
  assert(p_list);

  if (p_list->nodes[item_pos].prev == TRASH_PREV) {
    printf("Can't insert: incorrect position.\n"
           "Size: %-4zu. Your position: %-4zu\n",
           p_list->size, item_pos);
    return;
  }

  if (item_pos != p_list->size - 1) {
    p_list->linerazed = false;
  }

  if (p_list->size == p_list->capacity) {
    size_t new_capacity = p_list->capacity * 2;
    realloc_list(p_list, new_capacity);
    p_list->capacity = new_capacity;
  }

  item_t *data = p_list->data;

  int new_free_pos = abs(p_list->nodes[p_list->free_pos]
                             .next); // запоминаем следующий свободный элемент
  p_list->nodes[p_list->nodes[item_pos].next].prev = p_list->free_pos;
  data[p_list->free_pos] = item; // записываем на свободное место новый элемент
  p_list->nodes[p_list->free_pos].next =
      p_list->nodes[item_pos]
          .next; // записываем в next под новым элементом следующий (он был
                 // записан под тем, после которого мы хотим вставить новый)
  p_list->nodes[item_pos].next =
      p_list->free_pos; // теперь новый элемент -  следующий для того, после
                        // которого мы его вставили
  p_list->nodes[p_list->free_pos].prev =
      item_pos; // предыдущий для нового мы передаем как аргументом
  p_list->free_pos = new_free_pos; // записываем новое свободное место
  p_list->size++; // размер увеличился
}

item_t list_delete(list *const p_list, const size_t item_pos) {
  assert(p_list);

  if (p_list->nodes[item_pos].prev == TRASH_PREV || item_pos == 0) {
    printf("Can't delete: incorrect position.\n"
           "Size: %-4zu. Your position: %-4zu\n",
           p_list->size, item_pos);
    return 0;
  }

  if (item_pos != p_list->size - 1) {
    p_list->linerazed = false;
  }

  if (p_list->capacity == p_list->size * 4 && p_list->linerazed == true) {
    size_t new_capacity = p_list->capacity / 2;
    realloc_list(p_list, new_capacity);
    p_list->capacity = new_capacity;
  }

  item_t item = p_list->data[p_list->nodes[item_pos].prev];
  p_list->nodes[p_list->nodes[item_pos].prev].next =
      p_list->nodes[item_pos].next;
  p_list->nodes[p_list->nodes[item_pos].next].prev =
      p_list->nodes[item_pos].prev;
  p_list->nodes[item_pos].next = TRASH_PREV;
  p_list->data[item_pos] = 0;
  p_list->nodes[item_pos].next = -p_list->free_pos;
  p_list->free_pos = item_pos;
  p_list->nodes[item_pos].prev = TRASH_PREV;
  p_list->size--;
  return item;
}

static void swap(list *const p_list, size_t i, size_t j) {
  item_t temp_data = p_list->data[i];
  p_list->data[i] = p_list->data[j];
  p_list->data[j] = temp_data;

  p_list->nodes[p_list->nodes[j].next].prev = i;
  p_list->nodes[p_list->nodes[j].prev].next = i;

  node temp_node = p_list->nodes[i];
  p_list->nodes[i] = p_list->nodes[j];
  p_list->nodes[j] = temp_node;

  p_list->nodes[p_list->nodes[j].next].prev = j;
  p_list->nodes[p_list->nodes[j].prev].next = j;
}

static void swap_free(list *const p_list, size_t i, size_t j) {
  p_list->nodes[p_list->nodes[j].next].prev = i;
  p_list->nodes[p_list->nodes[j].prev].next = i;

  p_list->nodes[i].next = p_list->nodes[j].next;
  p_list->nodes[i].prev = p_list->nodes[j].prev;
  p_list->data[i] = p_list->data[j];

  if (j == p_list->capacity - 1)
    p_list->nodes[j].next = TRASH_NEXT;
  else
    p_list->nodes[j].next = -j - 1;

  p_list->nodes[j].prev = TRASH_PREV;
  p_list->data[j] = 0;
}

void quick_list_sort(list *const p_list) {
  for (int i = 1; i < p_list->size; i++) {
    if (p_list->nodes[i].prev != -1 &&
        p_list->nodes[p_list->nodes[i - 1].next].prev != -1)
      swap(p_list, i, p_list->nodes[i - 1].next);
    else
      swap_free(p_list, i, abs(p_list->nodes[i - 1].next));
  }

  for (size_t i = p_list->size; i < p_list->capacity; i++) {
    p_list->data[i] = 0;
    p_list->nodes[i].next = -i - 1;
    p_list->nodes[i].prev = TRASH_PREV;
  }

  p_list->nodes[p_list->capacity - 1].next = TRASH_NEXT;
  p_list->nodes[p_list->capacity - 1].prev = TRASH_PREV;
  p_list->linerazed = true;

  if (p_list->size != p_list->capacity)
    p_list->free_pos = p_list->size;
  else
    p_list->free_pos = 0;
}

void list_sort(list *const p_list) {
  item_t *data = (item_t *)calloc(p_list->capacity, sizeof(item_t));
  node *nodes = (node *)calloc(p_list->capacity, sizeof(node));

  data[0] = p_list->data[0];
  nodes[0].prev = p_list->size - 1;
  nodes[0].next = 1;
  int p_next = p_list->nodes[0].next;
  for (size_t i = 1; i < p_list->size; i++) {
    data[i] = p_list->data[p_next];
    p_next = p_list->nodes[p_next].next;
    nodes[i].next = i + 1;
    nodes[i].prev = i - 1;
  }
  nodes[p_list->size - 1].next = 0;

  for (size_t i = p_list->size; i < p_list->capacity; i++) {
    data[i] = 0;
    nodes[i].next = -i - 1;
    nodes[i].prev = -1;
  }
  nodes[p_list->capacity - 1].next = TRASH_NEXT;
  nodes[p_list->capacity - 1].prev = TRASH_PREV;

  if (p_list->size != p_list->capacity)
    p_list->free_pos = p_list->size;

  free(p_list->data);
  free(p_list->nodes);

  p_list->data = data;
  p_list->nodes = nodes;
  p_list->linerazed = true;
}
