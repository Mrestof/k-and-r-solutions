#include <stdio.h>
#include "lib/myutils.h"

#define MAXL 1'000
#define TS 8

int main() {
  char line[MAXL];
  int i, linelen;
  int col = 0;

  while ((linelen = getline(line, MAXL)) > 0)
    for (i = 0; i < linelen; i++) {
      if (line[i] != '\t') {
        putchar(line[i]);
        col = col == TS-1 ? 0 : col+1;
        continue;
      }
      for (; TS - col > 0; col++)
        putchar(' ');
      col = 0;
    }

  return 0;
}
