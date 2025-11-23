#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "lib/myutils.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void itob(char buf[], const int n, const int base) {
  int i;
  int digits, d;

  if ((digits = n) < 0) {
    if (n == INT_MIN)
      digits = -(n+1);
    else
      digits = -n;
  }

  i = 0;
  do {
    d = digits % base + '0';
    if (base > 10 && d > '9')
      d += 'a' - '9' - 1;
    buf[i++] = d;
  } while ((digits /= base) > 0);

  if (n < 0) {
    if (n == INT_MIN)
      ++buf[0];  // yes, I'm incrementing a char, god bless ascii
    buf[i++] = '-';
  }

  buf[i] = '\0';

  reverse(buf);
}

void test_itob(const int n, const int base, const char sol[]) {
  char buf[256];
  buf[0] = '\0';

  printf("base:%2d inp:%d\n", base, n);
  fflush(stdout);
  itob(buf, n, base);
  if (strcmp(buf, sol) == 0) {
    printf(ANSI_COLOR_GREEN "out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%s]" ANSI_COLOR_RESET "\n", sol);
    printf(ANSI_COLOR_YELLOW "act_out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
}

int main() {
  // Tiny suite for K&R 3-5 nya~
  test_itob(0,          2,  "0");       // base-2 zero purr
  test_itob(15,         2,  "1111");    // binary stretch nya
  test_itob(25,         3,  "221");    // trinary base :3
  test_itob(31,         5,  "111");     // base-5 transition nya
  test_itob(255,        8,  "377");     // octal max byte meow
  test_itob(42,         10, "42");      // decimal meow
  test_itob(-42,        10, "-42");
  test_itob(1234,       12, "86a");     // dozenal digits uwu
  test_itob(255,        16, "ff");      // hex
  test_itob(-255,       16, "-ff");
  test_itob(1024,       20, "2b4");     // base-20 mixed letters
  test_itob(448834,     27, "mlid");    // beyond hex
  test_itob(INT_MAX,    36, "zik0zj");  // INT_MAX edge w/ large base
  test_itob(INT_MIN,    36, "-zik0zk"); // INT_MAX edge w/ large base
  return 0;
}
