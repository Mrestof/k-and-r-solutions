#include <math.h>
#include <stdio.h>
#include <ctype.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRECISION 1e-15

// don't expect beauty from this function please, I just wanted to make it
// work, so lots of repeating stuff that would be better moved to separate
// functions :')
double naive_atof(const char s[]) {
  double val, power;
  int i, j, sign;
  int nexp, exp_sign;

  for (i = 0; isspace(s[i]); i++)
    ;

  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++;

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  if (s[i] == 'e' || s[i] == 'E') {
    i++;

    exp_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;

    for (nexp = 0; isdigit(s[i]); i++)
      nexp = 10 * nexp + (s[i] - '0');

    for (j = 0; j < nexp; j++)
      if (exp_sign == 1)
        val *= 10;
      else
        val /= 10;
  }

  return sign * val / power;
}

void test_naive_atof(const char s[], const double sol) {
  double out, diff;

  printf("s:[%s]\n", s);
  fflush(stdout);

  out = naive_atof(s);
  diff = fabs(out - sol);

  if (diff < PRECISION) {
    printf(
      ANSI_COLOR_GREEN "out:[%g] diff:[%g]" ANSI_COLOR_RESET "\n", sol, diff
    );
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%g]" ANSI_COLOR_RESET "\n", sol);
    printf(ANSI_COLOR_YELLOW "act_out:[%g]" ANSI_COLOR_RESET "\n", out);
    printf(ANSI_COLOR_YELLOW "diff:[%g]" ANSI_COLOR_RESET "\n", diff);
  }
}

int main() {
  // manual

  // ai
  test_naive_atof("0", 0.0);
  test_naive_atof("123.456", 123.456);
  test_naive_atof("-78.9", -78.9);
  test_naive_atof("   +42.0", 42.0);        // leading spaces + sign
  test_naive_atof("3.14159e0", 3.14159);    // exponent zero
  test_naive_atof("-1.23E+3", -1230.0);
  test_naive_atof("6.022e23", 6.022e23);
  test_naive_atof("9.81e-2", 0.0981);
  test_naive_atof(".5", 0.5);               // missing leading digit
  test_naive_atof("500.", 500.0);           // missing fractional digits
  test_naive_atof(" \t-0.001e-3", -1.0e-6); // whitespace tabs + small exp
  test_naive_atof("junk", 0.0);             // expect zero if no digits parsed


  return 0;
}
