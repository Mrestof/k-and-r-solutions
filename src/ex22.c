#include <stdio.h>

int readline(char line[], int maxline);

int main() {
  char line[100];
  for (int i = 0; i < 3; ++i) {
    readline(line, 100);
    printf("%s", line);
  }
  return 0;
}

int readline(char s[], int lim) {
  int c, i;
  int run = 1;

  i = 0;
  while (run) {
    if (i >= lim-1)
      run = 0;
    else if ((c=getchar())==EOF)
      run = 0;
    else if (c=='\n')
      run = 0;
    else {
      s[i] = c;
      ++i;
    }
  }

  // for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
  //     s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

