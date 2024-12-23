#include <stdio.h>
#include <stdlib.h>

#include "include/compiler.h"
#include "include/lexer.h"
#include "include/recursive_decent.h"

int main() {
  array idents = {};
  array tokens = {};

  tokenize("examples/factorial.ll", &idents, &tokens);
  Tree *program = create_tree(&tokens);
  compile_tree("asmcode.asm", program);

  array_dtor(&idents, 1);
  array_dtor(&tokens, 0);
  tree_dtor(program);
  /*
  Tree* program = tree_read(&idents, "tree");
  compile_tree("asmcode", program);
  array_dtor(&idents, 1);
  */
  return 0;
}
