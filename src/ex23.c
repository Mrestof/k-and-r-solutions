#include <stdio.h>

int naive_htoi(char s[]) {
  int i;
  int curn, resn;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    i = 2;
  else
    i = 0;;
  for (resn = 0; s[i] != '\0'; ++i) {
    if (s[i] >= '0' && s[i] <= '9')
      curn = s[i] - '0';
    else if (s[i] >= 'a' && s[i] <= 'f')
      curn = s[i] - 'a' + 10;
    else if (s[i] >= 'A' && s[i] <= 'F')
      curn = s[i] - 'A' + 10;
    else
     return -1;
    resn = resn * 16 + curn;
  }

  return resn;
}

void test_naive_htoi(char s[]) {
  printf("%s:\t%d\n", s, naive_htoi(s));
}

int main() {
  test_naive_htoi("0Xf1");
  test_naive_htoi("0XF1");
  test_naive_htoi("0xf1");
  test_naive_htoi("0xF1");
  test_naive_htoi("f1");
  test_naive_htoi("F1");
  test_naive_htoi("0xc0ffee");
  return 0;
}
