#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int prevch = '\0';

int getch(void) {
  if (prevch != '\0') {
    prevch = '\0';
    return prevch;
  }
  return getchar();
}

int ungetch(int c) {
  if (prevch != '\0') {
    printf("ungetch: too many characters\n");
    return 1;
  }
  prevch = c;
  return 0;
}

// return EOF for end of file, zero if the next input is not a number, and a
// positive value if the input contains a valid number
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch()))
    /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(c);
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

int main() {
  int c = 0;
  int s, n;
  while (c < 5) {
    s = getint(&n);
    if (s == EOF)
      return 0;
    if (s == 0)
      continue;
    if (s > 0) {
      printf("found int: %d\n", n);
      c++;  // hehe
    }
  }
  return 0;
}
