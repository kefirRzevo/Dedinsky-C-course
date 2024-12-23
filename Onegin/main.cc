#include "include/functions.hh"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp = fopen("res/Hamlet.txt", "r");
  int size_of_file = size_file(fp);
  char *text = (char *)calloc(size_of_file + 1, sizeof(char));
  int text_size = fread(text, sizeof(char), size_of_file, fp) - 1;
  int num_str = how_many_strings(text, text_size);
  struct String *string = (struct String *)calloc(num_str, sizeof(*string));
  filling(string, text_size, text);
  QuickSort(string, num_str - 1, comp);
  conclusion(string, num_str, "hamlet1.txt");
  QuickSort(string, num_str - 1, comp_back);
  conclusion(string, num_str, "hamlet2.txt");
  free(text);
  free(string);
  fclose(fp);
  return 0;
}
