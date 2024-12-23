#include "../include/table.h"

static hash_t qhash(const void *const data, const size_t size) {
  const char *byte = (char *)data;
  const char *const lastByte = byte + size;
  hash_t hash = 0;

  while (byte < lastByte)
    hash = ((hash << 0x8) + (hash >> 0x8)) ^ *byte++;

  return hash;
}

void table_ctor(hash_table *p_hash_table, size_t table_size) {
  assert(p_hash_table);

  list *p_table = (list *)calloc(table_size, sizeof(list));

  for (size_t i = 0; i < table_size; i++) {
    list_ctor(&p_table[i]);
  }

  p_hash_table->table = p_table;
  p_hash_table->size = table_size;
}

void table_dtor(hash_table *p_hash_table) {
  assert(p_hash_table);
  size_t sum = 0;
  for (size_t i = 0; i < p_hash_table->size; i++) {
    list_dump(&p_hash_table->table[i]);
    list_dtor(&p_hash_table->table[i]);
  }
  free(p_hash_table->table);
  p_hash_table->size = 0;
}

void add_item(hash_table *p_hash_table, item_t *item) {
  assert(p_hash_table);

  hash_t hash = qhash(item->mas, strlen(item->mas));

  node *found_node =
      list_data_search(&p_hash_table->table[hash % p_hash_table->size], *item);
  if (found_node) {
    found_node->data.size++;
  } else {
    item->size = 1;
    list_insert_head(&p_hash_table->table[hash % p_hash_table->size], *item);
  }
}

void delete_item(hash_table *p_hash_table, item_t *item) {
  assert(p_hash_table);

  hash_t hash = qhash(item->mas, strlen(item->mas));
  node *found_node =
      list_data_search(&p_hash_table->table[hash % p_hash_table->size], *item);
  if (!found_node) {
    if (found_node->data.size > 1) {
      found_node->data.size--;
    } else {
      list_delete_node(&p_hash_table->table[hash % p_hash_table->size],
                       found_node);
    }
  }
}

void table_search(hash_table *p_hash_table, item_t *item) {
  assert(p_hash_table);

  hash_t hash = qhash(item->mas, strlen(item->mas));
  node *found_node =
      list_data_search(&p_hash_table->table[hash % p_hash_table->size], *item);
  if (found_node) {
    *item = found_node->data;
  } else {
    item->size = 0;
  }
}
