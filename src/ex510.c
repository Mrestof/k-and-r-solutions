#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
  if (sp >= MAXVAL) {
    printf("error: stack full, can't push %g\n", f);
    exit(EXIT_FAILURE);
  }
  val[sp++] = f;
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp <= 0) {
    printf("error: stack empty\n");
    exit(EXIT_FAILURE);
  }
  return val[--sp];
}

/* getop: get next character or numeric operand */
int getop(char* arg, char s[]) {
  int i;

  if (!isdigit(*arg) && *arg != '.') {
    if (*arg != '-')
      return *arg;
    if (!*++arg)
      return *--arg;
    --arg;
  }
  i = 0;
  if (isdigit(*arg) || *arg == '-') {
    s[i] = *arg;
    while (isdigit(s[++i] = *++arg))
      ;
  }
  if (*arg == '.')
    while (isdigit(s[++i] = *++arg))
      ;
  return NUMBER;
}

/* reverse Polish calculator */
int main(int argc, char *argv[]) {
  (void)argc;
  char type;
  double op2;
  char s[MAXOP];

  argv++;
  while (*argv) {
    type = getop(*argv++, s);
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
      if (op2 == 0.0) {
        printf("error: zero divisor\n");
        return 1;
      }
      push(pop() / op2);
      break;
    default:
      printf("error: unknown command %s\n", s);
      return 1;
      break;
    }
  }
  printf("%.8g\n", pop());
  return 0;
}
