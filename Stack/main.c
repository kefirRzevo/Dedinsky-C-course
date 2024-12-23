#include "include/stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  stack stack0 = {};
  stack stack1 = {};
  StackCtor(&stack0);
  StackDump(&stack0);
  StackPush(&stack0, 11);
  StackPush(&stack0, 13);
  StackPush(&stack0, 17);
  StackDump(&stack0);
  StackPush(&stack0, 23);
  StackPush(&stack0, 29);
  StackPush(&stack0, 31);
  StackDump(&stack0);
  double a = 0;
  StackPop(&stack0, &a);
  StackPop(&stack0, &a);
  StackPop(&stack0, &a);
  StackPop(&stack0, &a);
  StackPop(&stack0, &a);
  StackPop(&stack0, &a);
  StackPop(&stack0, &a);
  printf("%lg\n", a);
  StackDump(&stack0);
  StackDump(&stack1);
  StackCtor(&stack1);
  StackDump(&stack1);
  return 0;
}
