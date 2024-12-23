#include "../include/akinator.h"
#include <ctype.h>

char *iterator = NULL;

static void get_file_size(FILE *const file, size_t *file_size);

static void get_nodes(char *buff, node *p_node, char *end_file, tree *p_tree);

static void get_file_size(FILE *const file, size_t *file_size) {
  size_t current_position = 0;

  current_position = (size_t)ftell(file);
  fseek(file, 0L, SEEK_END);
  *file_size = (size_t)ftell(file) + 1;
  fseek(file, (long)current_position, SEEK_SET);
}

void get_tree_text(size_t *const file_size, char *textfile_path,
                   char **text_buff) {
  assert(textfile_path);

  FILE *txt_file = NULL;
  txt_file = fopen(textfile_path, "r");

  get_file_size(txt_file, file_size);
  *text_buff = (char *)calloc(*file_size, sizeof(char));

  fread(*text_buff, sizeof(char), *file_size, txt_file);
  fclose(txt_file);
}

static void get_nodes(char *buff, node *p_node, char *end_file, tree *p_tree) {
  if (buff > end_file)
    return;

  while (isspace(*iterator))
    iterator++;

  char *first_not_space = iterator;
  char *last_not_space = iterator;

  while (*iterator != '{' && *iterator != '}') {
    if (!isspace(*iterator)) {
      last_not_space = iterator;
    }
    iterator++;
  }

  p_node->data = first_not_space;
  if (*iterator == '{') {
    *(last_not_space + 1) = '\0';
    iterator++;

    node *new_lnode = (node *)calloc(1, sizeof(node));
    p_node->left = new_lnode;
    p_tree->size++;
    get_nodes(iterator, p_node->left, end_file, p_tree);

    while (*iterator != '{')
      iterator++;
    iterator++;

    node *new_rnode = (node *)calloc(1, sizeof(node));
    p_node->right = new_rnode;
    p_tree->size++;
    get_nodes(iterator, p_node->right, end_file, p_tree);
  } else if (*iterator == '}') {
    *(last_not_space + 1) = '\0';
    iterator++;
  }
}

void parse(char *buff, tree *p_tree, char *end_file) {
  while (*buff != '{' && buff < end_file)
    buff++;
  buff++;

  iterator = buff;

  get_nodes(buff, p_tree->root, end_file, p_tree);
}
