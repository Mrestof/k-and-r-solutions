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
  return 0;
}

int main(int argc, char* argv[]) {
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
