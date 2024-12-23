#include "../include/tree.h"

static const char *LOGFILE_PATH = "logs/dump";
static const char *DOT_PATH = "logs/tree";
static size_t N_DUMPS = 0;
static FILE *logfile = NULL;

static FILE *dump_init(const char *const dump_path);

static void dump_close();

static void make_one_dump(tree *p_tree, char *img_path);

static void print_nodes(node *tree_node, FILE *const dotfile);

static FILE *open_dot_txt(const char *const dot_path);

static void close_dot_txt(FILE *const dotfile);

static void dump_close() {
  fprintf(logfile, "\t</body>\n"
                   "</html>\n");
}

static FILE *dump_init(const char *const dump_path) {
  assert(dump_path);

  if (logfile == NULL) {
    logfile = fopen(dump_path, "w");

    fprintf(logfile, "<!doctype html>                                          "
                     "                   \n"
                     "<html>                                                   "
                     "                   \n"
                     "\t<head lang='en'>                                       "
                     "                   \n"
                     "\t\t<meta charset='utf-8'>                               "
                     "                   \n"
                     "\t\t<meta name='viewport' content='width=device-width'>  "
                     "                   \n"
                     "\t\t<title>List dump</title>                             "
                     "                   \n"
                     "\t\t<style>                                              "
                     "                   \n"
                     "\t\tbody {                                               "
                     "                   \n"
                     "\t\t}                                                    "
                     "                   \n"
                     "\t\t.list {                                              "
                     "                   \n"
                     "\t\t\twidth: max-content;                                "
                     "                   \n"
                     "\t\t\tfont-size: 20px;                                   "
                     "                   \n"
                     "\t\t\tpadding: 10px 20px;                                "
                     "                   \n"
                     "\t\t}                                                    "
                     "                   \n"
                     "\t\t.img {                                               "
                     "                   \n"
                     "\t\t\toverflow-x: auto;                                  "
                     "                   \n"
                     "\t\t}                                                    "
                     "                   \n"
                     "\t\t</style>                                             "
                     "                   \n"
                     "\t</head>                                                "
                     "                   \n"
                     "\t<body>                                                 "
                     "                   \n");
  }
  return logfile;
}

static void make_one_dump(tree *p_tree, char *img_path) {
  fprintf(logfile,
          "\t\t<hr width = '100%%'>\n"
          "\t\t<div class = 'list'>\n"
          "\t\t\t<pre>DUMP %zu</pre>\n"
          "\t\t\t<pre>List address: %p</pre>\n"
          "\t\t\t<pre>Size:         %zu</pre>\n"
          "\t\t</div>\n"
          "\t\t<div class = 'img'>\n"
          "\t\t\t<img src = \"../%s\" height = 500px>\n"
          "\t\t</div>",
          N_DUMPS + 1, p_tree, p_tree->size, img_path);
}

void tree_dump(tree *p_tree) {
  assert(p_tree);

  char cmd_string[64] = "";
  char dotfile_string[32] = "";
  char dump_path[32] = "";
  char img_path[32] = "";

  sprintf(dotfile_string, "%s%zu.dot", DOT_PATH, N_DUMPS);
  sprintf(img_path, "%s_img%zu.svg", DOT_PATH, N_DUMPS);
  sprintf(cmd_string, "dot %s -Tsvg -o %s", dotfile_string, img_path);
  sprintf(dump_path, "%s.html", LOGFILE_PATH);

  FILE *dotfile = open_dot_txt(dotfile_string);
  assert(dotfile);

  print_nodes(p_tree->root, dotfile);
  close_dot_txt(dotfile);

  system(cmd_string);

  logfile = dump_init(dump_path);
  make_one_dump(p_tree, img_path);
  atexit(dump_close);
  N_DUMPS++;
}

static FILE *open_dot_txt(const char *const dot_path) {
  assert(dot_path);

  FILE *dotfile = NULL;
  dotfile = fopen(dot_path, "w");

  fprintf(dotfile, "digraph G                                                  "
                   "                                        \n"
                   "{                                                          "
                   "                                        \n"
                   "\t\tbgcolor  = \"#FFFFFF\"                                 "
                   "                                        \n"
                   "\t\tcompound = true                                        "
                   "                                        \n"
                   "\t\tnewrank  = true                                        "
                   "                                        \n"
                   "\t\tgraph[splines = polyline, nodesep = 0.3, ranksep = 1, "
                   "rankdir = TB]                            \n"
                   "\t\tnode[shape = record, style = \"filled\", penwidth = 2, "
                   "color = \"#000000\", margin = 0.04,     \n"
                   "\t\tfontcolor = \"#000000\", fontsize = 8, fillcolor = "
                   "\"#FFFFFF\", fontname = \"Arial\"]          \n"
                   "\t\tedge[arrowsize = 0.7, style = solid, penwidth = 1.1, "
                   "color = \"#CCCCCC\"]                    \n\n");
  return dotfile;
}

static void close_dot_txt(FILE *const dotfile) {
  assert(dotfile);

  fprintf(dotfile, "}");
  fclose(dotfile);
}

static void print_nodes(node *tree_node, FILE *const dotfile) {
  if (tree_node == NULL) {
    return;
  }

  fprintf(dotfile, "\t\tNode%p[label = \"%s\"]\n", tree_node, tree_node->data);

  if (tree_node->left != NULL) {
    fprintf(dotfile,
            "\t\tNode%p -> Node%p[label = \"да\", color = \"black\", fontname "
            "= \"Arial\"]\n\n",
            tree_node, tree_node->left);
    print_nodes(tree_node->left, dotfile);
  }
  if (tree_node->right != NULL) {
    fprintf(dotfile,
            "\t\tNode%p -> Node%p[label = \"нет\", color = \"black\", fontname "
            "= \"Arial\"]\n\n",
            tree_node, tree_node->right);
    print_nodes(tree_node->right, dotfile);
  }

  fprintf(dotfile, "\n");
}
