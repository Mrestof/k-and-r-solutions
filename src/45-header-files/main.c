#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "calc.h"

#define MATH_SEP '$'
#define MAXOP 100

int main() {
  char c, type;
  double op2;
  char s[MAXOP];

  if (!isatty(STDIN_FILENO))
    // find and execute first block like an inline math in latex
    while ((c = getchar()) != MATH_SEP && c != EOF);

  while ((type = getop(s)) != EOF && type != MATH_SEP) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}
