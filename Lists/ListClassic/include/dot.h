#ifndef DOT_H
#define DOT_H

#include "list.h"

FILE *open_dot_txt(const char *const dotfile_path);

void print_nodes(const list *const p_list, FILE *const dotfile);

void close_dot_txt(FILE *const dotfile);

#endif
