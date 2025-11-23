#include <stdio.h>

#define LIBBSD_OPENBSD_VIS
#include <bsd/vis.h>

#define MAXLINE 2048

int readline(char line[], int maxline);
void reverse(char s[]);

int main() {
  char line[MAXLINE];
  char output[MAXLINE];

  while (readline(line, MAXLINE) != 0) {
    reverse(line);
    //printf("%s", line);
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

void reverse(char s[]) {
  int l, r;
  char tmp;

  l = 0;
  for (r = 0; s[r+1] != '\0'; ++r);
  if (s[r] == '\n') --r;

  while (l < r) {
    tmp = s[l];
    s[l] = s[r];
    s[r] = tmp;
    ++l;
    --r;
  }
}
