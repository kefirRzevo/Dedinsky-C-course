#include "include/akinator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error with filename\n");
    return 0;
  }
  char *text_file = argv[1];

  akinator(text_file);
  return 0;
}
