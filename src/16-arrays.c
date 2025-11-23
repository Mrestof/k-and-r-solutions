#include <stdio.h>

int main() {
  int c, i, nwhite, nother, ndigits;
  int ndigit[10];

  nwhite = nother = 0;
  for (i = 0; i < 10; i++)
    ndigit[i] = 0;

  while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9') {
      ++ndigit[c-'0'];
      ++ndigits;
    }
    else if (c == ' ' || c == '\n' || c == '\t')
      ++nwhite;
    else
      ++nother;

  for (i = 0; i < 10; ++i)
    printf("'%d': %d\n", i, ndigit[i]);
  printf("digigs: %d\n", ndigits);
  printf("blanks: %d\n", nwhite);
  printf("other: %d\n", nother);
  printf("total: %d\n", nwhite + nother + ndigits);
}
