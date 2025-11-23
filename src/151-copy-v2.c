#include <stdio.h>

// copy input to output; 1st version
int main() {
  printf("value of EOF is: '%d'\n", EOF);

  int c;
  while ((c = getchar()) != EOF)
    putchar(c);
}
