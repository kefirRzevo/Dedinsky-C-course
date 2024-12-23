#include "include/cpu.h"
#include "include/lexer.h"
#include "include/parser.h"

int main(int argc, const char* argv[]) {
  array idents_arr = {};
  array tokens_arr = {};
  if (argc != 2) {
    printf("Usage: <%s> <path_to_asm>\n", argv[0]);
    return 0;
  }

  if (!tokenize(argv[1], &idents_arr, &tokens_arr))
    assert(0);

  if (!create_binfile("binary", &tokens_arr))
    assert(0);

  processor("binary");
  array_dtor(&idents_arr, 1);
  array_dtor(&tokens_arr, 0);
  return 0;
}
