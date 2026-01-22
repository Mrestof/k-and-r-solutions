#include "lib/myutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 1'000
#define MAXT 100

int detab(int tabstops[]) {
  char line[MAXL];
  int i, linelen;
  int col = 0;
  int tsi = 0;

  while ((linelen = getline(line, MAXL)) > 0)
    for (i = 0; i < linelen; i++) {
      if (col >= tabstops[tsi] && tsi < MAXT)
        tsi++;
      if (line[i] != 't') {
        putchar(line[i]);
        col++;
        continue;
      }
      for (; tabstops[tsi] - col > 0; col++)
        putchar(' ');
    }

  return 0;
}

int entab(int tabstops[]) {
  char inpl[MAXL], outl[MAXL];
  int i, j, linelen;
  int tsi = 0;

  while ((linelen = getline(inpl, MAXL)) > 0) {
    for (i = j = 0; i < linelen; i++, j++) {
      if (i+1 == tabstops[tsi]) {
        tsi++;
        if (inpl[i] == ' ') {
          for (; j > 0 && outl[j - 1] == ' '; j--)
            outl[j] = '\0';
          outl[j] = 't';
          continue;
        }
      }
      outl[j] = inpl[i];
    }
  }

  printf("%s", outl);
  return 0;
}

int main(int argc, char* argv[]) {
  (void)argc;
  char *subprogname = *++argv;
  int tabstops[MAXT];
  int i;

  argv++;
  for (i = 0; argv[i]; i++)
    tabstops[i] = atoi(argv[i]);
  for (int ts = i>0?tabstops[i-1]/8+1:1; i < MAXT; i++)
    tabstops[i] = ts++*8;

  if (strcmp(subprogname, "detab") == 0)
    return detab(tabstops);
  if (strcmp(subprogname, "entab") == 0)
    return entab(tabstops);

  return 1;
}
