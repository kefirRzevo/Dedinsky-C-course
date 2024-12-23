#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <string.h>

using std::string;

const double EPS = 1e-9;

double compare(const double a) {
  double eps = 0.00000001, max = 1.e+100;

  if (abs(a) < eps)
    return 0;
  if (abs(a) > max)
    return max;
  else
    return a;
}

//----------------------------------------------------------------------------

int solve_eq(double a, double b, double c, double *x1, double *x2) {
  if (compare(a) == 0) {
    if (compare(b) == 0) {
      if (compare(c) == 0)
        return -1;
    } else /* if (b!=0)*/
    {
      *x1 = compare(-c / b);
      return 1;
    }
  } else {
    double d = b * b - 4 * a * c;
    if (compare(d) == 0) {
      *x1 = *x2 = compare(-b / (2 * a));

      return 1;
    }

    if (d < 0)
      return 0;
    else {
      double sqrt_d = sqrt(d);

      *x1 = compare((-b - sqrt_d) / (2 * a));
      *x2 = compare((-b + sqrt_d) / (2 * a));

      return 2;
    }
  }
  return 0;
}

//----------------------------------------------------------------------------

bool check_coeffs(string koef_a) {
  int schet = 0;
  int sch_tochek = 0;
  int schet_min = 0;

  for (int i = 0; i < (int)koef_a.size(); i++) {
    if ((koef_a[i] == '.') || (koef_a[i] >= '0' && koef_a[i] <= '9') ||
        (koef_a[i] == '-')) {
      if (koef_a[i] == '.') {
        sch_tochek++;
      }
      if (koef_a[i] == '-')
        schet_min++;
      else
        schet++;
    }
  }

  if (((schet + sch_tochek + schet_min) >= (int)koef_a.size()) &&
      (sch_tochek <= 1)) {
    if (((koef_a[0] == '-') && (schet_min == 1) && (koef_a[1] != '.')) ||
        (schet_min == 0))
      return true;
    else
      return false;
  }
  return 0;
}

//----------------------------------------------------------------------------

double get_number(string str_a, double *a) {

  const char *str_coef = str_a.c_str();
  int size = strlen(str_coef);

  double coef = 0;
  int point = 0;
  int check_minus = 0;

  if (str_coef[0] == '-')
    check_minus = 1;
  else
    check_minus = 0;

  for (int i = check_minus; i < size; i++) {
    coef = coef * 10 + (str_coef[i] - '0');
    if (str_coef[i + 1] == '.') {
      point = i + 1;
      break;
    }
  }

  if (point != 0) {
    for (int i = point + 1; i < size; i++) {
      coef = coef * 10 + (str_coef[i] - '0');
    }
    int amount_number_after_point = size - point - 1;
    for (int i = 0; i < amount_number_after_point; i++)
      coef /= 10;
  }

  if (check_minus == 1)
    coef *= (-1);

  return *a = coef;
}

//----------------------------------------------------------------------------

void output(int root, double x1, double x2) {
  switch (root) {
  case 0:
    printf("No roots \n\n");
    break;

  case -1:
    printf("All numbers are the roots \n\n");
    break;

  case 1:
    printf("The root is: %lg \n\n", x1);
    break;

  case 2:
    printf("The roots are: %lg and %lg \n\n", x1, x2);
    break;

  default:
    printf("The wrong number of the roots \n\n");
  }
}

//----------------------------------------------------------------------------

bool check_last_symbols(string str) {
  for (int i = 0; i < (int)str.size(); i++) {
    if (str[i] != ' ')
      return false;
  }
  return true;
}

//----------------------------------------------------------------------------

void solve_square(string str_a, string str_b, string str_c, string str) {
  if (check_coeffs(str_a) && check_coeffs(str_b) && check_coeffs(str_c) &&
      check_last_symbols(str)) {
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    a = get_number(str_a, &a);
    b = get_number(str_b, &b);
    c = get_number(str_c, &c);

    int root = solve_eq(compare(a), compare(b), compare(c), &x1, &x2);
    printf("Your coeffitients: %lg  %lg  %lg \n", compare(a), compare(b),
           compare(c));
    output(root, x1, x2);
  } else
    printf("Check your coeffitiens, please\nn");
}

//----------------------------------------------------------------------------

int main() {
  for (int i = 0; i < 100; i++) {
    printf("Enter the coefficients of the equation ");
    ///  fgets (aa, sizeof (aa), stdin);
    string str_a, str_b, str_c, str;     //
    std::cin >> str_a >> str_b >> str_c; //

    std::getline(std::cin, str); //

    check_last_symbols(str);
    solve_square(str_a, str_b, str_c, str);
  }

  return 0;
}
