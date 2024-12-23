#include "../include/tree.h"

static void tree_delete(node **tree_node);

static void tree_pre_order_pass(node *p_node, FILE *datafile, size_t* lvl);

void tree_ctor(tree **p_tree) {
  tree *new_tree = (tree *)calloc(1, sizeof(tree));
  *p_tree = new_tree;
  node *root = (node *)calloc(1, sizeof(node));

  (*p_tree)->root = root;
  (*p_tree)->size = 0;
}

static void tree_pre_order_pass(node *p_node, FILE *datafile, size_t *lvl) {

  if (p_node == NULL)
    return;

  fprintf(datafile, "\n");

  for (size_t i = 0; i < *lvl; i++)
    fprintf(datafile, "\t");

  fprintf(datafile, "{%" SPECIFICATOR "", p_node->data);
  (*lvl)++;

  tree_pre_order_pass(p_node->left, datafile, lvl);
  tree_pre_order_pass(p_node->right, datafile, lvl);

  (*lvl)--;

  if (p_node->left != NULL && p_node->right != NULL) {
    fprintf(datafile, "\n");

    for (size_t j = 0; j < *lvl; j++)
      fprintf(datafile, "\t");

    fprintf(datafile, "}");
    return;
  }

  fprintf(datafile, "}");
}

void tree_print(tree *p_tree, FILE *datafile) {
  assert(p_tree);
  size_t init_lvl = 0;

  tree_pre_order_pass(p_tree->root, datafile, &init_lvl);
}

static void tree_delete(node **tree_node) {
  if (*tree_node != NULL) {
    tree_delete(&((*tree_node)->left));
    tree_delete(&((*tree_node)->right));
    free(*tree_node);
    *tree_node = NULL;
  }
}

void tree_dtor(tree *p_tree) {
  assert(p_tree);
  tree_delete(&(p_tree->root));
  free(p_tree);
}
