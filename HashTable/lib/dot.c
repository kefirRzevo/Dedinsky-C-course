#include "../include/list.h"

static size_t N_NODES = 1;

FILE *open_dot_txt(const char *const dot_path) {
  assert(dot_path);
  FILE *dotfile = NULL;
  dotfile = fopen(dot_path, "w");
  fprintf(dotfile, "digraph G \n{\n"
                   "\tgraph[rankdir = LR]\n"
                   "\tnode[shape = box, fontsize = 8]\n\n");
  return dotfile;
}

void close_dot_txt(FILE *const dotfile) {
  assert(dotfile);

  fprintf(dotfile, "}");
  fclose(dotfile);
}

void print_nodes(const list *const p_list, FILE *const dotfile) {
  assert(dotfile);
  assert(p_list);

  node *p_node = p_list->tail;
  while (p_node != NULL) {
    fprintf(
        dotfile,
        "\tsubgraph cluster%zi\n\t{\n"
        "\t\tmargin = 0\n"
        "\t\tlabel  = %zu\n"
        "\t\tNode%p[shape = record, label = \" word: %s | size: %" SPECIFICATOR
        " | <n>next: %p | <p>prev: %p\"]\n"
        "\t}\n",
        N_NODES, N_NODES, p_node, p_node->data.mas, p_node->data.size,
        p_node->next, p_node->prev);
    if (p_node->next != NULL) {
      fprintf(dotfile, "\t\tNode%p:n -> Node%p:n[color = \"red\"]\n\n", p_node,
              p_node->next);
    }
    p_node = p_node->next;
    N_NODES++;
  }
  fprintf(dotfile, "\n");
}
