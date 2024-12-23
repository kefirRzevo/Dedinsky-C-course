#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int GetG(const char *str);
int GetN();
int GetE();
int GetP();
int GetT();

const char *s = NULL;
int p = 0;

int main() {
  printf("%d", GetG("20*30+(10+5*2)+1$"));
  return 0;
}

int GetG(const char *str) {
  s = str;
  p = 0;
  int val = GetE();
  assert(s[p] == '$');
  return val;
}

int GetE() {
  int val = 0;
  val = GetT();
  while (s[p] == '+' || s[p] == '-') {
    int op = s[p];
    p++;
    int val2 = GetT();
    if (op == '+')
      val += val2;
    else
      val -= val2;
  }
  return val;
}

int GetT() {
  int val = 0;
  val = GetP();
  while (s[p] == '*' || s[p] == '/') {
    int op = s[p];
    p++;
    int val2 = GetP();
    if (op == '*')
      val *= val2;
    else
      val /= val2;
  }
  return val;
}

int GetP() {
  int val = 0;
  if (s[p] == '(') {
    p++;
    val = GetE();
    assert(s[p] == ')');
    p++;
    return val;
  } else {
    return GetN();
  }
}

int GetN() {
  int val = 0;
  while ('0' <= s[p] && s[p] <= '9') {
    val = val * 10 + (s[p] - '0');
    p++;
  }
  return val;
}
