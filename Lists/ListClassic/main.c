#include "include/dump.h"
#include "include/list.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  list lst = {};
  list_ctor(&lst);
  list_insert_tail(&lst, 10);
  list_insert_tail(&lst, 20);
  list_insert_tail(&lst, 30);
  list_insert_tail(&lst, 120);
  list_insert_tail(&lst, 330);
  list_insert_tail(&lst, 37);
  list_dump(&lst);
  list_delete_head(&lst, NULL);
  list_delete_head(&lst, NULL);
  list_delete_head(&lst, NULL);
  list_insert_head(&lst, 666);
  list_insert_head(&lst, 62);
  list_dump(&lst);
  list_dtor(&lst);
  return 0;
}
