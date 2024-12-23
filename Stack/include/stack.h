#ifndef STACK_H
#define STACK_H

#include "config.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef double item_t;

#ifdef StackCanaryProtect
typedef long long int canary_t;
#endif

#ifdef StackHashProtect
typedef size_t hash_t;
#endif

#define SPECIFICATOR "lg"
#define CANARY_SPECIFICATOR "llX"
#define HASH_SPECIFICATOR "zu"
#define N_INVALIDS 11

typedef struct {
#ifdef StackCanaryProtect
  canary_t LeftCanary;
#endif

  item_t *data;
  size_t size;
  size_t capacity;

#ifdef StackHashProtect
  hash_t hash;
#endif

#ifdef StackCanaryProtect
  canary_t RightCanary;
#endif
} stack;

void StackCtor(stack *const p_stack);

void StackDtor(stack *const p_stack);

void StackPush(stack *const p_stack, const item_t element);

void StackPop(stack *const p_stack, item_t *const p_element);

void StackDump(const stack *const p_stack);

#define StackCtor(p_stack) stack_ctor(p_stack, #p_stack);
#define StackDtor(p_stack) stack_dtor(p_stack, #p_stack);
#define StackPush(p_stack, element) stack_push(p_stack, #p_stack, element);
#define StackPop(p_stack, p_element) stack_pop(p_stack, #p_stack, p_element);
#define StackDump(p_stack) stack_dump(p_stack, #p_stack);

void stack_ctor(stack *const p_stack, const char *const stack_name);

void stack_dtor(stack *const p_stack, const char *const stack_name);

void stack_push(stack *const p_stack, const char *const stack_name,
                const item_t element);

void stack_pop(stack *const p_stack, const char *const stack_name,
               item_t *const p_element);

void stack_dump(stack *const p_stack, const char *const stack_name);

enum StackError {
  INVALID_DATA = 1 << 0,
  INVALID_SIZE = 1 << 1,
  INVALID_CAPACITY = 1 << 2,
  INVALID_STACK_REINITIALIZIED = 1 << 3,
  INVALID_STACK_UNITIALIZED = 1 << 4,
  INVALID_EMPTY_STACK = 1 << 5,
  INVALID_HASH = 1 << 6,
  INVALID_DATA_LCNRY = 1 << 7,
  INVALID_DATA_RCNRY = 1 << 8,
  INVALID_STACK_LCNRY = 1 << 9,
  INVALID_STACK_RCNRY = 1 << 10,
};

typedef enum {
  ctor = 1,
  push = 2,
  dump = 3,
  pop = 4,
  dtor = 5,
} Functions;

#endif // STACK_H
