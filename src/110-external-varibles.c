#include <stdio.h>

#define LIBBSD_OPENBSD_VIS
#include <bsd/vis.h>

#define MAXLINE 1000

int max;
char line[MAXLINE];
char longest[MAXLINE];

int readline(void);
void copy(void);

int main() {
  int len;
  extern int max;
  extern char longest[];
  char output[MAXLINE];

  max = 0;
  while ((len = readline()) > 0)
    if (len > max) {
      max = len;
      copy();
    }

  if (max > 0) {
    strvis(output, longest, VIS_TAB | VIS_NL | VIS_CSTYLE);
    printf("longest line: '%s'\n", output);
    printf("longest line length: '%d'\n", max);
  }

  return 0;
}

int readline(void) {
  int c, i;
  extern char line[];

  for (i=0; (c=getchar())!=EOF && c!='\n'; ++i)
    if (i < MAXLINE-1)
      line[i] = c;
  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';

  return i;
}

void copy(void) {
  int i;
  extern char line[], longest[];

  i = 0;
  while ((longest[i] = line[i]) != '\0')
    ++i;
}
