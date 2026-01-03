#include <ctype.h>
#include <stdio.h>

#define PREVCHSIZE 2
int prevch[PREVCHSIZE];
int n_prevch = 0;

int getch(void) {
  if (n_prevch)
    return prevch[--n_prevch];
  return getchar();
}

int ungetch(int c) {
  if (n_prevch >= PREVCHSIZE) {
    printf("ungetch: too many characters\n");
    return 1;
  }
  prevch[n_prevch++] = c;
  return 0;
}

// return EOF for end of file, zero if the next input is not a number, and a
// positive value if the input contains a valid number
int getfloat(double *pn) {
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
  if (c == '.') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(c);
      ungetch('.');
      return 0;
    }
    for (int exp = 10; isdigit(c); exp*=10, c = getch())
      *pn = *pn + (double)(c - '0') / exp;
  }
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

int main() {
  int c = 0;
  int s;
  double n;
  while (c < 9) {
    s = getfloat(&n);
    if (s == EOF)
      return 0;
    if (s == 0) {
      while (!isspace(getch()))
        // skip till the end of the word
        ;
      continue;
    }
    if (s > 0) {
      printf("found int: %.10g\n", n);
      c++;  // hehe
    }
  }
  return 0;
}
