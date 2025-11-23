#include <stdio.h>

int main() {
  int i, c;
  int chars[128];

  for (i = 0; i < 128; ++i)
    chars[i] = 0;

  while ((c = getchar()) != EOF)
    ++chars[c];

  for (c = 0; c < 128; ++c) {
    if (chars[c] == 0) continue;
    if (c == '\n')
      printf("'\\n':");
    else if (c == '\t')
      printf("'\\t':");
    else
      printf("'%c': ", c);
    for (i = 0; i < chars[c]; ++i)
      putchar('#');
    putchar('\n');
  }
}
