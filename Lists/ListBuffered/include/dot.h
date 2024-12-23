#ifndef DOT_H
#define DOT_H

#include "list.h"

FILE *open_dot_txt(const char *const dotfile_path);

void print_node(const list *const p_list, const size_t num_node,
                FILE *const dotfile);

void close_dot_txt(FILE *const dotfile);

#endif
