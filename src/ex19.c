#include <stdio.h>

int main() {
  int c, pc;

  for (pc = -1; (c = getchar()) != EOF; pc = c)
    if (!(c == pc && c == ' '))
      putchar(c);
}
