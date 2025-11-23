#include <stdio.h>

#define LIBBSD_OPENBSD_VIS
#include <bsd/vis.h>

#define MAXLINE 2048

int readline(char line[], int maxline);

int main() {
  int i;
  int blanks, len;
  bool first_char;
  char line[MAXLINE];
  char output[MAXLINE];


  while ((len = readline(line, MAXLINE)) != 0) {
    blanks = 0;
    first_char = false;
    for (i = len-1; i >= 0; --i) {
      if (line[i] == ' ' || line[i] == '\t') ++blanks;
      else if (!first_char && line[i] != '\n') {
        first_char = true;
        line[i+1] = '\n';
        line[i+2] = '\0';
      }
    }
    if (blanks == len-1) continue;
    strvis(output, line, VIS_TAB | VIS_NL | VIS_CSTYLE);
    printf("line: '%s'\n", output);
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
