#include "../include/dot.h"
#include "../include/list.h"

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

void print_node(const list *const p_list, const size_t num_node,
                FILE *const dotfile) {
  assert(dotfile);
  assert(p_list);

  fprintf(dotfile,
          "\t\tsubgraph cluster%zu{\n"
          "\t\tmargin = 0\n"
          "\t\tlabel  = %zu\n"
          "\t\t%zu[shape = record, label = \"item: %" SPECIFICATOR
          " | <n>next: %d | <p>prev: %d\"]\n"
          "\t\t}\n",
          num_node, num_node, num_node, p_list->data[num_node],
          p_list->nodes[num_node].next, p_list->nodes[num_node].prev);

  if (p_list->nodes[num_node].prev != TRASH_PREV) {
    fprintf(dotfile, "\t\t%zu:n -> %d:n[color = \"blue\"]\n", num_node,
            p_list->nodes[num_node].next);
  } else if (p_list->nodes[num_node].next == TRASH_NEXT) {
    fprintf(dotfile, "\t\t%zu:n -> TRASH[color = \"red\", style = dashed]\n",
            num_node);
  } else {
    fprintf(dotfile, "\t\t%zu:n -> %d:n[color = \"red\"]\n", num_node,
            abs(p_list->nodes[num_node].next));
  }

  fprintf(dotfile, "\n");
}
