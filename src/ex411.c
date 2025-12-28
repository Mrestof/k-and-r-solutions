#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MATH_SEP '$'

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

int bufp = 0; /* next free position in buf */
char buf[BUFSIZE]; /* buffer for ungetch */

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

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

/* getop: get next character or numeric operand */
int getop(char s[]) {
  bool isnum;
  char c, cprev;
  int i;

  // just moving `bufp` and `buf` here as static variables and copy pasting
  // logic from `getch` and `ungetch` to replace calls to them sounds not very
  // interesting or hard, so I'm not going to do that

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

/* reverse Polish calculator */
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
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        // I'm too lazy to check if user inputs integers here, and I will
        // personally rip user's arms off if they try using modulo on floating
        // point
        push((int)pop() % (int)op2);
      else
        printf("error: zero divisor\n");
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
