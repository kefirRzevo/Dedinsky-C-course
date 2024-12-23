#include "../include/parser.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t INIT_N_CMDS = 10;

static array labels = {};
static array commands = {};
static token *p_tokens = NULL;
static size_t iterator = 0;

static bool GetG();
static bool GetE();
static bool GetT();
static bool GetP();
static bool GetU();

static char *is_lab(size_t position);
static bool is_num(size_t position);
static bool is_reg(size_t position);
static bool is_command(size_t position);
static char is_ch(size_t position);
static char is_keyword(size_t position, char name);

static const char *get_cmd_string(char type);
static const char *get_reg_string(char type);
static char get_cmd_num(const char *command);
static char get_reg_num(const char *registry);
static bool print_error(const char *waited);
static int add_cmd(char key, type_of_argument type, double argument);

static int fill_labels();
static int commands_dump(const char *dump_file_path);
static int write_cmds(const char *binfile_path);

static const char *get_cmd_string(char type) {
#define DEF_CMD(name, cmd, num_arg, code) else if (cmd == type) return #name;

  if (0) {
  }
#include "../src/commands.def"
#undef DEF_CMD

  return NULL;
}

static const char *get_reg_string(char type) {
#define DEF_REG(name, reg) else if (reg == type) return #name;

  if (0) {
  }
#include "../src/registers.def"
#undef DEF_REG

  return NULL;
}

static char get_cmd_num(const char *command) {
#define DEF_CMD(name, cmd, num_arg, code)                                      \
  else if (!strncmp(#name, command, sizeof(#name))) return cmd;

  if (0) {
  }
#include "../src/commands.def"
#undef DEF_CMD

  return 0;
}

static char get_reg_num(const char *registry) {
#define DEF_REG(name, reg)                                                     \
  else if (!strncmp(#name, registry, sizeof(#name))) return reg;

  if (0) {
  }
#include "../src/registers.def"
#undef DEF_REG

  return 0;
}

static bool print_error(const char *waited) {
  fprintf(stderr, "%d\tMistake at line %zu: waited \"%s\", in fact ", __LINE__,
          p_tokens[iterator].line, waited);
  switch (p_tokens[iterator].type) {
  case CMD:
    fprintf(stderr, "COMMAND \"%s\".\n",
            get_cmd_string(p_tokens[iterator].value.command));
    break;
  case REG:
    fprintf(stderr, "REGISTER \"%s\".\n",
            get_reg_string(p_tokens[iterator].value.reg));
    break;
  case NUM:
    fprintf(stderr, "NUMBER \"%lg\".\n", p_tokens[iterator].value.number);
    break;
  case KW:
    fprintf(stderr, "KEYWORD \"%c\".\n", p_tokens[iterator].value.keyword);
    break;
  case CH:
    fprintf(stderr, "CHAR \"%c\".\n", p_tokens[iterator].value.ch);
    break;
  case LAB:
    fprintf(stderr, "LABEL \"%s\".\n", p_tokens[iterator].value.label);
    break;
  default:
    fprintf(stderr, "unpredictable error.\n");
  }
  return NULL;
}

static int add_cmd(char key, type_of_argument type, double argument) {

#define DEF_CMD(name, cmd, num_arg, code)                                      \
  else if (cmd == key && num_arg == 0 && type != is_nothing) {                 \
    fprintf(stderr, "%d\tCommand %s hasn't got arguments.", __LINE__, #name);  \
    return 0;                                                                  \
  }

  if (0) {
  }
#include "../src/commands.def"
#undef DEF_CMD

  Command temp_cmd = {};

  temp_cmd.key = key;
  temp_cmd.argument_type = type;
  temp_cmd.argument = argument;

  if (!array_push(&commands, &temp_cmd))
    return 0;

  return 1;
}

static char *is_lab(size_t position) {
  if (p_tokens[position].type == LAB)
    return p_tokens[position].value.label;
  return NULL;
}

static bool is_num(size_t position) { return (p_tokens[position].type == NUM); }

static bool is_reg(size_t position) { return (p_tokens[position].type == REG); }

static bool is_command(size_t position) {
  return p_tokens[position].type == CMD;
}

static char is_ch(size_t position) {
  if (p_tokens[position].type == CH)
    return p_tokens[position].value.ch;
  return 0;
}

static char is_keyword(size_t position, char name) {
  if (p_tokens[position].type == KW)
    if (p_tokens[position].value.keyword == name)
      return name;
  return 0;
}

static bool GetG() {
  while (!is_keyword(iterator, '$')) {
    if (is_lab(iterator) && is_keyword(iterator + 1, ':')) {
      labeled_cmd temp = {};
      temp.label = is_lab(iterator);
      temp.to = -1;
      temp.from = commands.size;

      if (!array_push(&labels, &temp))
        return false;

      iterator += 2;
    } else if (is_command(iterator) && is_command(iterator + 1) ||
               is_command(iterator) && is_lab(iterator + 1) &&
                   is_keyword(iterator + 2, ':') ||
               is_command(iterator) && is_keyword(iterator + 1, '$')) {
      add_cmd(p_tokens[iterator].value.command, is_nothing, 0);
      iterator++;
    } else if (is_command(iterator) && is_keyword(iterator + 1, '\'') &&
               is_ch(iterator + 2) && is_keyword(iterator + 3, '\'')) {
      add_cmd(p_tokens[iterator].value.command, is_char, is_ch(iterator + 2));
      iterator += 4;
    } else if (is_command(iterator) && is_lab(iterator + 1) &&
               !is_keyword(iterator + 2, ':')) {
      labeled_cmd temp = {};
      temp.label = is_lab(iterator + 1);
      temp.to = commands.size;
      temp.from = -1;

      if (!array_push(&labels, &temp))
        return false;

      add_cmd(p_tokens[iterator].value.command, is_label, -2);
      iterator += 2;
    } else if (is_command(iterator) && is_reg(iterator + 1)) {
      add_cmd(p_tokens[iterator].value.command, is_register,
              p_tokens[iterator + 1].value.reg);
      iterator += 2;
    } else if (is_command(iterator) && is_num(iterator + 1)) {
      add_cmd(p_tokens[iterator].value.command, is_number,
              p_tokens[iterator + 1].value.number);
      iterator += 2;
    } else if (is_command(iterator) && is_keyword(iterator + 1, '[')) {
      char command_key = p_tokens[iterator].value.command;
      iterator += 2;

      if (!GetE())
        return false;

      if (!is_keyword(iterator, ']'))
        return print_error("]");

      add_cmd(get_cmd_num("pop"), is_register, get_reg_num("drk"));
      add_cmd(command_key, is_ram_register, get_reg_num("drk"));

      iterator++;
    } else {
      return print_error("command");
    }
  }

  if (iterator > 1) {
    iterator -= 2;
    if (is_lab(iterator) && is_keyword(iterator + 1, ':'))
      return print_error("ending program with no label");
  }

  return true;
}

static bool GetE() {
  GetT();
  while ((is_keyword(iterator, '+') || is_keyword(iterator, '-')) &&
         !is_keyword(iterator, '$')) {
    if (is_keyword(iterator, '+')) {
      iterator++;
      if (!GetT())
        return false;

      add_cmd(get_cmd_num("add"), is_nothing, 0);
    } else if (is_keyword(iterator, '-')) {
      iterator++;
      if (!GetT())
        return false;

      add_cmd(get_cmd_num("sub"), is_nothing, 0);
    }
  }
  return true;
}

static bool GetT() {
  GetU();
  while ((is_keyword(iterator, '*') || is_keyword(iterator, '/')) &&
         !is_keyword(iterator, '$')) {
    if (is_keyword(iterator, '*')) {
      iterator++;
      if (!GetU())
        return false;

      add_cmd(get_cmd_num("mul"), is_nothing, 0);
    } else if (is_keyword(iterator, '/')) {
      iterator++;
      if (!GetU())
        return false;

      add_cmd(get_cmd_num("div_"), is_nothing, 0);
    }
  }
  return true;
}

static bool GetU() {
  if (is_reg(iterator)) {
    add_cmd(get_cmd_num("push"), is_register, p_tokens[iterator].value.reg);
    iterator++;
  } else if (is_num(iterator)) {
    add_cmd(get_cmd_num("push"), is_number, p_tokens[iterator].value.number);
    iterator++;
  } else if (is_keyword(iterator, '(')) {
    iterator++;
    if (!GetE())
      return false;

    if (!is_keyword(iterator, ')'))
      return print_error(")");

    iterator++;
  } else {
    return print_error("unary expression");
  }
  return true;
}

static int fill_labels() {
  for (size_t i = 0; i < labels.size; i++) {
    labeled_cmd temp1 =
        *((labeled_cmd *)((char *)labels.data + i * labels.item_size));
    Command temp_cmd =
        *((Command *)((char *)commands.data + temp1.to * commands.item_size));

    for (size_t j = 0; j < labels.size; j++) {
      labeled_cmd temp2 =
          *((labeled_cmd *)((char *)labels.data + j * labels.item_size));

      if (!strcmp(temp1.label, temp2.label) && i != j) {
        if (temp1.to == -1 && temp2.to == -1) {
          fprintf(stderr, "Label %s: is used more than one time.\n",
                  temp1.label);
          return 0;
        }
        if (temp1.from == -1 && temp2.to == -1) {
          temp_cmd.argument = temp2.from;
          *((Command *)((char *)commands.data +
                        temp1.to * commands.item_size)) = temp_cmd;
        }
      }
    }

    if (temp1.from == -1) {
      if (temp_cmd.argument == -2) {
        fprintf(stderr, "Label %s: is not found.\n", temp1.label);
        return 0;
      }
    }
  }
  return 1;
}

static int write_cmds(const char *binfile_path) {
  assert(binfile_path);

  FILE *binfile = fopen(binfile_path, "wb");
  if (!binfile)
    return 0;

  fwrite(&commands.size, sizeof(size_t), 1, binfile);
  fwrite(commands.data, sizeof(Command), commands.size, binfile);

  fclose(binfile);
  return true;
}

array *create_binfile(const char *binfile_path, array *tokens) {
  if (!array_ctor(&labels, sizeof(labeled_cmd)))
    return NULL;

  if (!array_ctor(&commands, sizeof(Command))) {
    array_dtor(&labels, 0);
    return NULL;
  }

  p_tokens = (token *)tokens->data;

  if (!GetG()) {
    array_dtor(&labels, 0);
    array_dtor(&commands, 0);
    return NULL;
  }

  if (!fill_labels()) {
    array_dtor(&labels, 0);
    array_dtor(&commands, 0);
    return NULL;
  }

  if (!write_cmds(binfile_path)) {
    array_dtor(&labels, 0);
    array_dtor(&commands, 0);
    return NULL;
  }

  if (!commands_dump("logs/cmds_dump.txt")) {
    array_dtor(&labels, 0);
    array_dtor(&commands, 0);
    return NULL;
  }

  array_dtor(&labels, 0);
  array_dtor(&commands, 0);

  return tokens;
}

static int commands_dump(const char *dump_file_path) {
  const time_t seconds = time(NULL);
  const struct tm *const date = localtime(&seconds);
  FILE *const logfile = fopen(dump_file_path, "w");
  if (!logfile)
    return 0;

  char day[16] = "";

  switch (date->tm_wday) {
  case 0:
    strcpy(day, "Sunday");
    break;
  case 1:
    strcpy(day, "Monday");
    break;
  case 2:
    strcpy(day, "Tuesday");
    break;
  case 3:
    strcpy(day, "Wednesday");
    break;
  case 4:
    strcpy(day, "Thursday");
    break;
  case 5:
    strcpy(day, "Friday");
    break;
  case 6:
    strcpy(day, "Saturday");
    break;
  default:
    break;
  }

  fprintf(
      logfile,
      "ASSEMBLER LOGFILE\n"
      "Time: %02d:%02d:%02d\n"
      "Day:  %s\n"
      "====================================================================\n"
      "|    |Type of argument:   |Command                                 |\n"
      "====================================================================\n",
      date->tm_hour, date->tm_min, date->tm_sec, day);

  for (size_t i = 0; i < commands.size; i++) {
    Command temp_cmd = {};
    memcpy(&temp_cmd, (char *)commands.data + i * sizeof(Command),
           sizeof(Command));

    fprintf(logfile, "|%-4zu|", i);
    switch (temp_cmd.argument_type) {
    case is_register:
      fprintf(logfile, "REGISTER            |    %-6s%-30s|\n",
              get_cmd_string(temp_cmd.key),
              get_reg_string((char)temp_cmd.argument));
      break;
    case is_number:
      fprintf(logfile, "NUMBER              |    %-6s%-30lg|\n",
              get_cmd_string(temp_cmd.key), temp_cmd.argument);
      break;
    case is_ram_register:
      fprintf(logfile,
              "RAM                 |    %-5s[%-4s]                         |\n",
              get_cmd_string(temp_cmd.key),
              get_reg_string((char)temp_cmd.argument));
      break;
    case is_char:
      fprintf(logfile, "CHAR                |    %-6s%-30c|\n",
              get_cmd_string(temp_cmd.key), (char)temp_cmd.argument);
      break;
    case is_nothing:
      fprintf(logfile, "NOTHING             |    %-36s|\n",
              get_cmd_string(temp_cmd.key));
      break;
    case is_label:
      fprintf(logfile, "LABEL               |    %-6s%-30d|\n",
              get_cmd_string(temp_cmd.key), (int)temp_cmd.argument);
      break;
    default:
      fprintf(stderr, "%zu|%lg|%d|%d\n", i, temp_cmd.argument,
              temp_cmd.argument_type, temp_cmd.key);
      assert(0);
      break;
    }
    fprintf(logfile, "========================================================="
                     "===========\n");
  }

  fclose(logfile);
  return 1;
}
