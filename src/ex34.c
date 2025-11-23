#include <limits.h>
#include <stdio.h>

#include "lib/myutils.h"

void itoa(char s[], const int n) {
  int i, d;

  if ((d = n) < 0) {
    if (n == INT_MIN)
      d = -(n+1);
    else
      d = -n;
  }

  i = 0;
  do {
    s[i++] = d % 10 + '0';
  } while ((d /= 10) > 0);

  if (n < 0) {
    if (n == INT_MIN)
      ++s[0];  // yes, I'm incrementing a char, god bless ascii
    s[i++] = '-';
  }

  s[i] = '\0';

  reverse(s);
}

void test_itoa(int n) {
  char buf[256];
  itoa(buf, n);
  printf("%d: %s\n", n, buf);
}

int main() {
  test_itoa(0);
  test_itoa(1);
  test_itoa(-1);
  test_itoa(1337);
  test_itoa(-1337);
  test_itoa(INT_MAX-1);
  test_itoa(INT_MIN+1);
  test_itoa(INT_MAX);
  test_itoa(INT_MIN);  // be careful nya
  return 0;
}
