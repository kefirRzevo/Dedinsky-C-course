#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int item_t;

#define SPECIFICATOR "d"
#define N_INVALIDS 11

static const size_t CAPACITY = 50;

typedef struct {
  item_t *data;
  size_t size;
  size_t capacity;
  size_t tail;
  size_t head;
} queue;

void queue_ctor(queue *const p_queue);

void queue_dtor(queue *const p_queue);

void push_head(queue *const p_queue, const item_t element);

void pop_tail(queue *const p_queue, item_t *const p_element);

void queue_dump(queue *const p_queue);

enum QueueError {
  INVALID_DATA = 1 << 0,
  INVALID_CAPACITY = 1 << 1,
  INVALID_QUEUE_REINITIALIZIED = 1 << 2,
  INVALID_QUEUE_UNITIALIZED = 1 << 3,
  INVALID_EMPTY_QUEUE = 1 << 4,
};

#endif // QUEUE_H
