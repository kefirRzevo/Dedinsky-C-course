#include "../include/list.h"

static const char *LOGFILE_PATH = "logs/dump";
static const char *DOT_PATH = "logs/list";
static size_t N_DUMPS = 0;
static FILE *logfile = NULL;

static FILE *dump_init(const char *const dump_path);

static void make_one_dump(const list *const p_list, char *img_path);

void dump_close() {
  fprintf(logfile, "\n\t</body>\n"
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

static void make_one_dump(const list *const p_list, char *img_path) {
  fprintf(logfile,
          "\t\t<hr width = '100%%'>\n"
          "\t\t<div class = 'list'>\n"
          "\t\t\t<pre>DUMP %zu</pre>\n"
          "\t\t\t<pre>List address: %p</pre>\n"
          "\t\t\t<pre>Size:         %zu</pre>\n"
          "\t\t</div>\n"
          "\t\t<div class = 'img'>\n"
          "\t\t\t<img src = \"../../../%s\" height = 500px>\n"
          "\t\t</div>",
          N_DUMPS + 1, p_list, p_list->size, img_path);
}

void list_dump(const list *const p_list) {
  assert(p_list);

  char cmd_string[128] = "";
  char dotfile_string[64] = "";
  char dump_path[64] = "";
  char img_path[64] = "";

  sprintf(dotfile_string, "%s%zu.dot", DOT_PATH, N_DUMPS);
  sprintf(img_path, "%s_img%zu.svg", DOT_PATH, N_DUMPS);
  sprintf(cmd_string, "dot %s -Tsvg -o %s", dotfile_string, img_path);
  sprintf(dump_path, "%s.html", LOGFILE_PATH);

  FILE *dotfile = open_dot_txt(dotfile_string);
  print_nodes(p_list, dotfile);
  close_dot_txt(dotfile);
  system(cmd_string);

  if (!logfile) {
    atexit(dump_close);
  }

  logfile = dump_init(dump_path);
  assert(logfile);
  make_one_dump(p_list, img_path);
  N_DUMPS++;
}
