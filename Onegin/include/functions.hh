struct String {
  char *begin;
  int len;
};

bool comp(char *beg1, char *beg2, int len1, int len2);
bool comp_back(char *beg1, char *beg2, int len1, int len2);
void BubbleSort(struct String *string, int size,
                bool comparator(char *beg1, char *beg2, int len1, int len2));
int partition(struct String *string, int low, int high,
              bool comparator(char *beg1, char *beg2, int len1, int len2));
void QuickSort_prototype(struct String *string, int low, int high,
                         bool (*comparator)(char *beg1, char *beg2, int len1,
                                            int len2));
void filling(struct String *string, int text_size, char *text);
int how_many_strings(char *text, int text_size);
void conclusion(struct String *string, int num_str, const char *file_name);
int size_file(FILE *fp);
void QuickSort(struct String *string, int size,
               bool (*comparator)(char *beg1, char *beg2, int len1, int len2));

template <typename T> void swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}

int size_file(FILE *fp) {
  fseek(fp, 0L, SEEK_END);
  int size_of_file = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  return size_of_file;
}

bool comp(char *beg1, char *beg2, int len1, int len2) {
  if (*beg1 == '\n')
    return true;
  for (char *i = beg1, *j = beg2; i - beg1 < len1 || j - beg2 < len2;
       i++, j++) {
    while (!isalpha(*i))
      i++;
    while (!isalpha(*j))
      j++;

    if (toupper(*i) > toupper(*j))
      return true;
    if (toupper(*i) < toupper(*j))
      return false;
  }
  return false;
}

bool comp_back(char *beg1, char *beg2, int len1, int len2) {
  if (*beg1 == '\n')
    return true;
  for (char *i = beg1 + len1 - 1, *j = beg2 + len2 - 1; i >= beg1 || j >= beg2;
       i--, j--) {
    while (!isalpha(*i))
      i--;
    while (!isalpha(*j))
      j--;

    if (toupper(*i) > toupper(*j))
      return true;
    if (toupper(*i) < toupper(*j))
      return false;
  }
  return false;
}

void QuickSort(struct String *string, int size,
               bool (*comparator)(char *beg1, char *beg2, int len1, int len2)) {
  int low = 0;
  int high = size - 1;
  QuickSort_prototype(string, low, high, comparator);
}

void BubbleSort(struct String *string, int size,
                bool comparator(char *beg1, char *beg2, int len1, int len2)) {
  int n;
  while (size) {
    n = 0;
    for (int j = 1; j < size; j++)
      if (comparator(string[j - 1].begin, string[j].begin, string[j - 1].len,
                     string[j].len)) {
        swap(string[j - 1], string[j]);
        n = j;
      }
    size = n;
  }
}

void QuickSort_prototype(struct String *string, int low, int high,
                         bool (*comparator)(char *beg1, char *beg2, int len1,
                                            int len2)) {
  if (low < high) {
    int pi = partition(string, low, high, comparator);
    QuickSort_prototype(string, low, pi - 1, comparator);
    QuickSort_prototype(string, pi + 1, high, comparator);
  }
}

int partition(struct String *string, int low, int high,
              bool (*comparator)(char *beg1, char *beg2, int len1, int len2)) {
  char *pivot_ch = string[high].begin;
  int pivot = string[high].len;
  int i = (low - 1);
  for (int j = low; j <= high - 1; j++) {
    if (comparator(pivot_ch, string[j].begin, pivot, string[j].len)) {
      i++;
      swap(string[i], string[j]);
    }
  }
  swap(string[i + 1], string[high]);
  return (i + 1);
}

void filling(struct String *string, int text_size, char *text) {
  string[0].begin = &text[0];
  for (int i = 0, j = 0; i <= text_size; i++) // rename j
  {
    if (text[i] == '\n') {
      string[j + 1].begin = &text[i] + 1;
      string[j].len = string[j + 1].begin - string[j].begin - 1;
      j++;
    }
  }
}

int how_many_strings(char *text, int text_size) {
  int num_str = 0;
  if (text[text_size] != '\n') {
    text_size++;
    text[text_size] = '\n';
  }
  for (int i = 0; i <= text_size; i++)
    if (text[i] == '\n')
      num_str++;
  return num_str;
}

void conclusion(struct String *string, int num_str, const char *file_name) {
  FILE *output = fopen(file_name, "w");
  for (int i = 0; i < num_str; i++) {
    if (*string[i].begin == '\n')
      continue;
    if (*string[i].begin == ' ') {
      int number_of_spaces = 0;
      for (char *j = string[i].begin; j - string[i].begin < string[i].len; j++)
        if (*j == ' ')
          number_of_spaces++;
      if (number_of_spaces == string[i].len)
        continue;
    }
    fwrite(string[i].begin, sizeof(char), string[i].len + 1, output);
  }
}
