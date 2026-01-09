#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

#include "lib/myutils.h"

int readline(char* s, int lim) {
  const char *sc = s;
  int c;

  for (; (c=getchar())!=EOF && c!='\n' && lim > 0; s++, lim--)
    *s = c;
  if (c == '\n' && lim > 0)
    *s++ = c;
  *s = '\0';

  return s - sc;
}

void reverse(char* s) {
  char *sr = s, c;

  while (*sr != '\0')
    sr++;
  sr--;

  for (; s < sr; s++, sr--) {
    c = *s;
    *s = *sr;
    *sr = c;
  }
}

void itoa(char* s, const int n) {
  char * ss = s;
  int d;

  if (n < 0) {
    if (n == INT_MIN)
      d = -(n+1);
    else
      d = -n;
  } else
    d = n;

  do
    *s++ = d % 10 + '0';
  while ((d /= 10) > 0);

  if (n < 0) {
    *s++ = '-';
  }
  *s = '\0';

  reverse(ss);

  if (n == INT_MIN)
    *--s += 1;  // yes, I'm incrementing a char, god bless ascii
}

int atoi(const char* s) {
  int n, sign;

  while (isspace(*s))
    s++;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (n = 0; isdigit(*s); s++)
    n = 10 * n + (*s - '0');

  return sign * n;
}

int strindex(const char* s, const char* const t) {
  // algo probably sucks in terms of simplicity and/or cpu time but ¯\_(ツ)_/¯
  const char *const sb = s;
  const char *st, *tt;

  if (*s == '\0' && *t == '\0')
    return 0;

  for (; *s != '\0'; s++) {
    for (st=s, tt=t; *st==*tt && *tt!='\0'; st++, tt++);
    if (*tt=='\0')
      return s - sb;
  }

  return -1;
}

void test_reverse(const char* const s, const char* const exp) {
  char buf[100];
  strcpy(buf, s);
  reverse(buf);
  if (strcmp(buf, exp) == 0)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(
    " : "
    "s='%s'"
    ",exp='%s'"
    ",res='%s'"
    RST "\n",
    s,
    exp,
    buf
  );
}

void test_itoa(const int n, const char* const exp) {
  char buf[100];
  itoa(buf, n);
  if (strcmp(buf, exp) == 0)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(
    " : "
    "n='%d'"
    ",exp='%s'"
    ",res='%s'"
    RST "\n",
    n,
    exp,
    buf
  );
}

void test_atoi(const char* const s, const int exp) {
  int res = atoi(s);
  if (res == exp)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(
    " : "
    "s='%s'"
    ",exp='%d'"
    ",res='%d'"
    RST "\n",
    s,
    exp,
    res
  );
}

void test_strindex(const char* const s, const char* const t, const int exp) {
  int res = strindex(s, t);
  if (res == exp)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(
    " : "
    "s='%s'"
    "t='%s'"
    ",exp='%d'"
    ",res='%d'"
    RST "\n",
    s,
    t,
    exp,
    res
  );
}

int main() {
  /* test_reverse calls */
  printf("--- reverse tests ---\n");
  test_reverse("hello", "olleh");
  test_reverse("world", "dlrow");
  test_reverse("a", "a");
  test_reverse("", "");
  test_reverse("ab", "ba");
  test_reverse("abc", "cba");
  test_reverse("abcd", "dcba");
  test_reverse("12345", "54321");
  test_reverse("racecar", "racecar");
  test_reverse("hello world", "dlrow olleh");
  test_reverse("A", "A");
  test_reverse("AB", "BA");
  test_reverse("Testing", "gnitseT");
  test_reverse("!@#$", "$#@!");
  test_reverse("123", "321");

  /* test_itoa calls */
  printf("--- itoa tests ---\n");
  test_itoa(0, "0");
  test_itoa(1, "1");
  test_itoa(-1, "-1");
  test_itoa(123, "123");
  test_itoa(-123, "-123");
  test_itoa(2147483647, "2147483647");
  test_itoa(-2147483648, "-2147483648");
  test_itoa(42, "42");
  test_itoa(-42, "-42");
  test_itoa(999, "999");
  test_itoa(-999, "-999");
  test_itoa(10, "10");
  test_itoa(-10, "-10");
  test_itoa(5000, "5000");
  test_itoa(-5000, "-5000");

  /* test_atoi calls */
  printf("--- atoi tests ---\n");
  test_atoi("0", 0);
  test_atoi("1", 1);
  test_atoi("-1", -1);
  test_atoi("123", 123);
  test_atoi("-123", -123);
  test_atoi("2147483647", 2147483647);
  test_atoi("-2147483648", -2147483648);
  test_atoi("42", 42);
  test_atoi("-42", -42);
  test_atoi("   123", 123);
  test_atoi("   -456", -456);
  test_atoi("789   ", 789);
  test_atoi("  +42", 42);
  test_atoi("0000123", 123);
  test_atoi("-0000456", -456);
  test_atoi("999abc", 999);
  test_atoi("abc123", 0);
  test_atoi("", 0);
  test_atoi("   ", 0);
  test_atoi("+", 0);
  test_atoi("-", 0);

  /* test_strindex calls */
  printf("--- strindex tests ---\n");
  test_strindex("hello world", "world", 6);
  test_strindex("hello world", "hello", 0);
  test_strindex("hello world", "o", 4);
  test_strindex("hello world", "l", 2);
  test_strindex("hello world", "xyz", -1);
  test_strindex("hello world", "", 0);
  test_strindex("", "hello", -1);
  test_strindex("", "", 0);
  test_strindex("abc", "abc", 0);
  test_strindex("abc", "bc", 1);
  test_strindex("abc", "c", 2);
  test_strindex("abc", "d", -1);
  test_strindex("abcabc", "abc", 0);
  test_strindex("abcdef", "def", 3);
  test_strindex("hello", "ll", 2);
  test_strindex("hello", "lo", 3);
  test_strindex("programming", "gram", 3);
  test_strindex("test", "testing", -1);
  test_strindex("aaa", "aa", 0);
  test_strindex("aaa", "aaa", 0);
  test_strindex("abcabcabc", "abc", 0);
  return 0;
}
