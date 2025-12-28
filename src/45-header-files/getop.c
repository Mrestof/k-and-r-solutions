#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "calc.h"

/* getop: get next character or numeric operand */
int getop(char s[]) {
  bool isnum;
  char c, cprev;
  int i;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  // is this nigerlicious or divine intellect?
  // also future note, please don't code before bed if sleepy, it's chaotic
  if (!isdigit(c) && c != '.') {
    if (c == '-') {
      cprev = c;
      isnum = isdigit(c = getch());
      ungetch(c);
      c = cprev;
      if (!isnum)
        return c;
    }
    else
      return c; /* not a number */
  }
  i = 0;
  if (isdigit(c) || c == '-') /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}
