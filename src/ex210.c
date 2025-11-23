#include <stdio.h>

char naive_tolower(char c);

int main() {
  char c;

  c = 'A';
  printf("A: %c\n", naive_tolower(c));
  c = 'D';
  printf("D: %c\n", naive_tolower(c));
  c = 'V';
  printf("V: %c\n", naive_tolower(c));
  c = 'b';
  printf("b: %c\n", naive_tolower(c));
  c = '!';
  printf("!: %c\n", naive_tolower(c));

  return 0;
}

char naive_tolower(char c) {
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
