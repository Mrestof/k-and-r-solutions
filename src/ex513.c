#include "lib/myutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMSIZE 1'000
#define MAXLINE 80
#define MAXPREV 20

char buf[MEMSIZE];
char *bp = buf;

char *alloc(int size) {
  if ((bp + size) - buf >= MEMSIZE)
    bp = buf;
  char *p = bp;
  bp += size;
  return p;
}

void cycle(int* n, int cycle_size) {
  *n = *n + 1 >= cycle_size ? 0 : *n + 1;
}

int main(int argc, char* argv[]) {
  int i;
  char line[MAXLINE];
  int linesize;
  int n;
  char *prevlines[MAXPREV] = {0};
  bool f_cycle = false;
  int pl_cur = 0;

  if (argc == 1)
    n = 3;  // BUG: infinite loop on n=1 and n=2
  else if (argc == 2)
    n = atoi(&argv[1][1]);
  else
    return 1;

  if (n <= 0)
    return 0;
  if (n > MAXPREV) {
    for (int c; (c = getchar()) != EOF; putchar(c));
    return 0;
  }

  while ((linesize = getline(line, MAXLINE)) > 0) {
    prevlines[pl_cur] = alloc(linesize+1);
    strcpy(prevlines[pl_cur], line);
    cycle(&pl_cur, n);
    if (!f_cycle && pl_cur == 0)
      f_cycle = true;
  }

  if (f_cycle) {
    for (i = pl_cur; i + 1 != pl_cur; cycle(&i, n))
      printf("%s", prevlines[i]);
    printf("%s", prevlines[i]);
  }
  else
    for (i = 0; i < pl_cur; i++)
      printf("%s", prevlines[i]);

  return 0;
}
