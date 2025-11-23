#include <stdio.h>

#define IN  1
#define OUT 0
#define MAXLEN 64

void print_horizontal(int wordlen[]) {
  int i, j;

  printf("Horizontal histogram of the lengths of words\n");

  for (i = 0; i < MAXLEN; ++i) {
    if (wordlen[i] == 0) continue;
    printf("%3d: ", i);
    for (j = 0; j < wordlen[i]; ++j)
      putchar('#');
    putchar('\n');
  }
}

void print_vertical(int wordlen[]) {
  int i, j;
  int max;

  printf("Vertical histogram of the lengths of words\n");

  max = wordlen[0];
  for (i = 0; i < MAXLEN; ++i)
    if (wordlen[i] > max)
      max = wordlen[i];

  for (i = 0; i < max; ++i) {
    for (j = 0; j < MAXLEN; ++j) {
      if (wordlen[j] == 0) continue;
      if (max - wordlen[j] > i)
        printf("   ");
      else
        printf("#  ");
    }
    putchar('\n');
  }
  for (i = 0; i < MAXLEN; ++i) {
    if (wordlen[i] == 0) continue;
    printf("%-3d", i);
  }
  putchar('\n');
}

int main() {
  int i;
  int c, state, len;
  int wordlen[MAXLEN];

  for (i = 0; i < MAXLEN; ++i)
    wordlen[i] = 0;

  state = OUT;
  len = 0;
  while((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        ++wordlen[len];
        len = 0;
      }
      state = OUT;
    }
    else {
      ++len;
      if (state == OUT)
        state = IN;
    }
  }

  print_horizontal(wordlen);
  print_vertical(wordlen);
}
