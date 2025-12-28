#include <stdio.h>

#include "calc.h"

#define BUFSIZE 100

int bufp = 0; /* next free position in buf */
char buf[BUFSIZE]; /* buffer for ungetch */

/* get a (possibly pushed-back) character */
char getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(char c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
