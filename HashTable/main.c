#include "include/table.h"

int main() {
  hash_table tab = {};
  table_ctor(&tab, 100);

  FILE *fp = fopen("res/Hamlet.txt", "r");
  size_t sum = 0;
  fscanf(fp, "%*[^A-Za-z]");

  while (!feof(fp)) {
    item_t temp = {};
    fscanf(fp, "%[A-Za-z]%*[^A-Za-z]", temp.mas);
    add_item(&tab, &temp);
    sum++;
  }
  printf("number of words: %zu\n", sum);

  item_t temp = {};
  strcat(temp.mas, "am");
  table_search(&tab, &temp);
  printf("the word %s meeted: %zu times\n", temp.mas, temp.size);

  fclose(fp);
  table_dtor(&tab);
  return 0;
}
