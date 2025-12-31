#include <stdio.h>

#define MAXNUMLEN 1000

void itoa(char buf[], int n) {
  int i;
  char c;

  if (n < 0) {
    n = -n;
    buf[0] = '-';
    buf[1] = '\0';
  }

  if (n >= 10) {
    itoa(buf, n/10);
    n %= 10;
  }

  c = '0' + n;

  for (i = 0; buf[i] != '\0'; i++);
  buf[i] = c;
  buf[i+1] = '\0';
}

int main() {
  char num[MAXNUMLEN];

  itoa(num, 0);
  printf("%s\n", num);
  num[0] = '\0';
  itoa(num, 1);
  printf("%s\n", num);
  num[0] = '\0';
  itoa(num, 123);
  printf("%s\n", num);
  num[0] = '\0';
  itoa(num, 241283);
  printf("%s\n", num);
  num[0] = '\0';

  itoa(num, -1);
  printf("%s\n", num);
  num[0] = '\0';
  itoa(num, -123);
  printf("%s\n", num);
  num[0] = '\0';
  itoa(num, -241283);
  printf("%s\n", num);
  num[0] = '\0';

  return 0;
}
