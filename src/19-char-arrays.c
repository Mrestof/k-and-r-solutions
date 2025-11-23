#include <stdio.h>

#define LIBBSD_OPENBSD_VIS
#include <bsd/vis.h>

#define MAXLINE 1000

int readline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
  int len;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];
  char output[MAXLINE];

  max = 0;
  while ((len = readline(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copy(longest, line);
    }

  if (max > 0) {
    strvis(output, longest, VIS_TAB | VIS_NL | VIS_CSTYLE);
    printf("longest line: '%s'\n", output);
    printf("longest line length: '%d'\n", max);
  }

  return 0;
}

int readline(char s[], int lim) {
  int c, i;

  for (i=0; (c=getchar())!=EOF && c!='\n'; ++i)
    if (i < lim-1)
      s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
