#ifndef PARSER_H
#define PARSER_H

#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void get_tree_text(size_t *const file_size, char *textfile_path,
                   char **text_buff);

void parse(char *buff, tree *p_tree, char *end_file);

#endif
