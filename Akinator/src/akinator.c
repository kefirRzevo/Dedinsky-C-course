#include "../include/akinator.h"
#include "../include/parser.h"
#include "../include/stack.h"
#include "../include/tree.h"

static const size_t Q_MAX_LEN = 30;
static const size_t A_MAX_LEN = 30;
static const size_t YN_MAX_LEN = 10;
static const size_t MODE_MAX_LEN = 20;

static const char yes[5] = "+";
static const char no[5] = "-";
static const char datafile_begin[16] = "akinator_tree";

static stack alloc_stack = {};
static size_t N_SAVINGS = 0;

static tree *make_tree(char *textfile_path, char *buff);

static mode handler();

static void akinator_guess(tree *p_tree);

static void akinator_compare(tree *p_tree);

static void akinator_define(tree *p_tree);

static void akinator_save(tree *p_tree);

static tree *make_tree(char *textfile_path, char *buff) {
  assert(textfile_path);

  size_t file_size = 0;
  tree *p_tree = NULL;

  get_tree_text(&file_size, textfile_path, &buff);
  tree_ctor(&p_tree);

  parse(buff, p_tree, buff + file_size);
  tree_dump(p_tree);
  return p_tree;
}

static mode handler() {
  char playing_mode_string[MODE_MAX_LEN] = "";
  fgets(playing_mode_string, MODE_MAX_LEN - 1, stdin);
  fseek(stdin, 0L, SEEK_END);
  playing_mode_string[strlen(playing_mode_string) - 1] = '\0';
  if (!strcmp("1", playing_mode_string))
    return GUESS;
  else if (!strcmp("2", playing_mode_string))
    return COMPARE;
  else if (!strcmp("3", playing_mode_string))
    return DEFINE;
  else if (!strcmp("4", playing_mode_string))
    return SAVE;
  else if (!strcmp("5", playing_mode_string))
    return EXIT;

  return YOU_PUT_HUYNYA;
}
// 05.03.21

void akinator(char *textfile_path) {
  assert(textfile_path);

  StackCtor(&alloc_stack);
  char *buff = NULL;
  tree *p_tree = make_tree(textfile_path, buff);
  StackPush(&alloc_stack, buff);

  for (;;) {
    printf("\nВведи \"enter\" чтобы начать, братишка");

    char check_symbol = 0;
    while (check_symbol != '\n')
      scanf("%c", &check_symbol);

    for (;;) {
      printf("\nДружище, выбирай режим:\n"
             "1 - Угадай мелодию,\n"
             "2 - Помереться писюнами,\n"
             "3 - Определитель Вандермонда,\n"
             "4 - Предохраняемся(я не про презервативы;)\n"
             "5 - Дружок-пирожок, не нажимай сюда\n\n");
      switch (handler()) {
      case GUESS:
        akinator_guess(p_tree);
        break;
      case COMPARE:
        akinator_compare(p_tree);
        break;
      case DEFINE:
        akinator_define(p_tree);
        break;
      case SAVE:
        akinator_save(p_tree);
        break;
      case EXIT:
        return;
      case YOU_PUT_HUYNYA:
        printf("Лень придумывать, скопипащу с енама: YOU_PUT_HUYNYA\n");
        break;
      }
    }
  }

  while (alloc_stack.size > 0) {
    void *temp_ptr = NULL;
    StackPop(&alloc_stack, &temp_ptr);
    free(temp_ptr);
  }
}

static void akinator_guess(tree *p_tree) {
  node *p_node = p_tree->root;
  for (;;) {
    if (p_node->left != NULL || p_node->right != NULL) {
    again1:
      printf("Братанчик, это же %s, да?\n", p_node->data);
      char yes_no_string[YN_MAX_LEN] = "";
      fgets(yes_no_string, YN_MAX_LEN - 1, stdin);
      yes_no_string[strlen(yes_no_string) - 1] = '\0';
      fseek(stdin, 0L, SEEK_END);

      if (!strcmp(yes, yes_no_string)) {
        p_node = p_node->left;
      } else if (!strcmp(no, yes_no_string)) {
        p_node = p_node->right;
      } else {
        printf("Для особо одаренных ответ это или да(%s), или нет(%s), "
               "третьего не дано\n",
               yes, no);
        goto again1;
      }
    } else {
    again2:
      printf("Это %s?\n", p_node->data);
      char yes_no_string[YN_MAX_LEN] = "";
      fgets(yes_no_string, YN_MAX_LEN - 1, stdin);
      yes_no_string[strlen(yes_no_string) - 1] = '\0';
      fseek(stdin, 0L, SEEK_END);

      if (!strcmp(yes, yes_no_string)) {
        printf("Попався розбийник\n\n");
        break;
      } else if (!strcmp(no, yes_no_string)) {
        printf("По моим подсчетам ты ввел хуйню, но я добавлю\n"
               "Кого добавлять, товарищ?\n");

        char user_answer[A_MAX_LEN] = "";
        fgets(user_answer, A_MAX_LEN, stdin);
        size_t user_ans_len = strlen(user_answer);
        user_answer[user_ans_len - 1] = '\0';
        fseek(stdin, 0L, SEEK_END);

        printf("А какая нахуй разница между %s и %s?\n", p_node->data,
               user_answer);

        char user_question[Q_MAX_LEN] = "";
        fgets(user_question, Q_MAX_LEN - 1, stdin);
        size_t user_que_len = strlen(user_question);
        user_question[user_que_len - 1] = '\0';
        fseek(stdin, 0L, SEEK_END);

        node *new_node_l = (node *)calloc(1, sizeof(node));
        node *new_node_r = (node *)calloc(1, sizeof(node));
        char *user_answer_buf = (char *)calloc(user_ans_len, sizeof(char));
        char *user_question_buf = (char *)calloc(user_que_len, sizeof(char));
        memcpy(user_answer_buf, user_answer, user_ans_len);
        memcpy(user_question_buf, user_question, user_que_len);
        StackPush(&alloc_stack, user_answer_buf);
        StackPush(&alloc_stack, user_question_buf);

        p_node->left = new_node_l;
        p_node->right = new_node_r;

        new_node_l->data = user_answer_buf;
        new_node_r->data = p_node->data;
        p_node->data = user_question_buf;

        printf("Записал в прошмандовки азербайджана\n");
        break;
      } else {
        printf("Бля, да ты заебал. Введи или да(%s), или нет(%s)\n", yes, no);
        goto again2;
      }
    }
  }
}

static node *find_path(node *p_node, stack *def_stack, char *elem) {
  node *found = NULL;

  if (!strcmp(elem, p_node->data)) {
    found = p_node;
  }
  if (p_node->left && !found) {
    found = find_path(p_node->left, def_stack, elem);
  }
  if (p_node->right && !found) {
    found = find_path(p_node->right, def_stack, elem);
  }

  if (found) {
    StackPush(def_stack, p_node);
  }
  return found;
}

static void akinator_define(tree *p_tree) {
  printf("Кого пробиваем\n");

  char user_def[A_MAX_LEN] = "";
  fgets(user_def, A_MAX_LEN, stdin);
  size_t user_def_len = strlen(user_def);
  user_def[user_def_len - 1] = '\0';
  fseek(stdin, 0L, SEEK_END);

  stack def_stack = {};
  StackCtor(&def_stack);

  node *found = find_path(p_tree->root, &def_stack, user_def);

  if (!found) {
    printf("Кентик, %s я не нашёл, извиняй братуха\n", user_def);
  } else {
    if (found->left != NULL || found->right != NULL) {
      printf("Улыбнись, потому что фронталка заполнила такого долбаеба, "
             "который вопрос блядь %s от определителя не отличает\n",
             user_def);
    } else {
      printf("Такс, с тебя 100500 дереввянных, братишку %s пробил\n", user_def);

      void *temp_ptr = NULL;
      StackPop(&def_stack, &temp_ptr);
      while (def_stack.size > 0) {
        void *temp_ptr_next = NULL;
        StackPop(&def_stack, &temp_ptr_next);
        if (((node *)temp_ptr)->left == (node *)temp_ptr_next) {
          printf("ебать он %s-> ", ((node *)temp_ptr)->data);
        } else {
          printf("чел реально не %s ->", ((node *)temp_ptr)->data);
        }
        temp_ptr = temp_ptr_next;
      }
      printf("%s\n\n", ((node *)temp_ptr)->data);
    }
  }
  StackDtor(&def_stack);
}

static void akinator_compare(tree *p_tree) {
input1:
  printf("Первого давай сюда\n");

  char first_elem[A_MAX_LEN] = "";
  fgets(first_elem, A_MAX_LEN, stdin);
  size_t first_elem_len = strlen(first_elem);
  first_elem[first_elem_len - 1] = '\0';
  fseek(stdin, 0L, SEEK_END);
input2:
  printf("А с кем мне его блядь сравнивать? Давай вводи\n");

  char second_elem[A_MAX_LEN] = "";
  fgets(second_elem, A_MAX_LEN, stdin);
  size_t second_elem_len = strlen(second_elem);
  second_elem[second_elem_len - 1] = '\0';
  fseek(stdin, 0L, SEEK_END);

  if (!strcmp(first_elem, second_elem)) {
    printf("Ах ты шутник, закинул одинаковых челиков и смеётся. На член свой "
           "посмотри, клоун хренов.\n");
    return;
  }

  stack def1_stack = {}, def2_stack = {};
  StackCtor(&def1_stack);
  StackCtor(&def2_stack);

  node *found1 = find_path(p_tree->root, &def1_stack, first_elem);
  node *found2 = find_path(p_tree->root, &def2_stack, second_elem);

  if (!found1) {
    printf("Насчет %s не подскажу, не видел такого\n", first_elem);
    goto input1;
  }
  if (!found2) {
    printf("Насчет %s не подскажу, не видел такого\n", second_elem);
    goto input2;
  }
  if (found1->left != NULL || found1->right != NULL) {
    printf("Щай бы вопрос %s(1) сравнивать\n", first_elem);
    goto input1;
  }
  if (found2->left != NULL || found2->right != NULL) {
    printf("Щай бы вопрос %s(2) сравнивать\n", second_elem);
    goto input2;
  }

  void *temp_ptr1 = NULL;
  void *temp_ptr2 = NULL;
  void *temp_ptr1_next = NULL;
  void *temp_ptr2_next = NULL;

  StackPop(&def1_stack, &temp_ptr1);
  StackPop(&def2_stack, &temp_ptr2);
  StackPop(&def1_stack, &temp_ptr1_next);
  StackPop(&def2_stack, &temp_ptr2_next);

  if (temp_ptr1_next == temp_ptr2_next) {
    printf("И %s, и %s", first_elem, second_elem);
  }
  while (temp_ptr1_next == temp_ptr2_next) {
    if (temp_ptr1_next == ((node *)temp_ptr1)->left) {
      printf(", %s", ((node *)temp_ptr1)->data);
    } else {
      printf(", не %s", ((node *)temp_ptr1)->data);
    }

    temp_ptr1 = temp_ptr1_next;
    temp_ptr2 = temp_ptr2_next;

    StackPop(&def1_stack, &temp_ptr1_next);
    StackPop(&def2_stack, &temp_ptr2_next);
  }
  printf("\n");

  if (temp_ptr1 == temp_ptr2 && temp_ptr1_next != temp_ptr2_next) {
    if (temp_ptr1_next == ((node *)temp_ptr1)->left) {
      printf("%s, в отличие от %s, %s", first_elem, second_elem,
             ((node *)temp_ptr1)->data);
    } else {
      printf("%s, в отличие от %s, %s", second_elem, first_elem,
             ((node *)temp_ptr2)->data);
    }
  }
  printf("\n");

  StackDtor(&def1_stack);
  StackDtor(&def2_stack);
}

static void akinator_save(tree *p_tree) {
  N_SAVINGS++;
  char datafile_path[32] = "";
  sprintf(datafile_path, "logs/%s%zu.txt", datafile_begin, N_SAVINGS);

  FILE *datafile = NULL;
  datafile = fopen(datafile_path, "w");

  tree_dump(p_tree);
  tree_print(p_tree, datafile);
  fclose(datafile);

  printf("Я сделаль\n");
}
