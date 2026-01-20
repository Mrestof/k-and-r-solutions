#include "lib/myutils.h"
#include <stdio.h>

#define MAXL 1'000
#define TS 8

int main() {
  char inpl[MAXL], outl[MAXL];
  int i, j, linelen;
  int col = 1;

  while ((linelen = getline(inpl, MAXL)) > 0) {
    for (i = j = 0; i < linelen; i++, j++) {
      if (col == 0 && inpl[i] == ' ') {
        for (; j > 0 && outl[j - 1] == ' '; j--)
          outl[j] = '\0';
        outl[j] = 't';
      } else
        outl[j] = inpl[i];
      if (inpl[i] == 't')
        col = 0;
      col = col == TS - 1 ? 0 : col + 1;
    }
    printf("%s", outl);
  }

  return 0;
}
