#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

#include "lib/myutils.h"

#define MATH_SEP '$'

#define NUMBER '0' /* signal that a number was found */
#define MATH '1' /* signal that a math function name was found */

#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* maximum depth of val stack */

#define MATH_FUNC_AMNT 22

#define LETTERS_AMNT 'z' - 'a' + 1

// math name mappings {{{

char *MATH_FUNC_NAME[MATH_FUNC_AMNT] = {
  "sin",
  "cos",
  "tan",
  "asin",
  "acos",
  "atan",
  "atan2",
  "sinh",
  "cosh",
  "tanh",
  "exp",
  "log",
  "log10",
  "pow",
  "sqrt",
  "ceil",
  "floor",
  "fabs",
  "ldexp", // not directly indexable
  "frexp", // not implemented
  "modf", // not implemented
  "fmod",
};

double (*MATH_FUNC_U[MATH_FUNC_AMNT])(double) = {
  sin,
  cos,
  tan,
  asin,
  acos,
  atan,
  NULL,
  sinh,
  cosh,
  tanh,
  exp,
  log,
  log10,
  NULL,
  sqrt,
  ceil,
  floor,
  fabs,
  NULL,
  NULL,
  NULL,
  NULL,
};

double (*MATH_FUNC_B[MATH_FUNC_AMNT])(double, double) = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  atan2,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  pow,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  fmod,
};

/// }}}

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

char buf = '\0'; /* buffer for ungetch */

double vars[LETTERS_AMNT+1] = {0}; // +1 for last printed variable

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
  char c;
  if (buf != '\0') {
    c = buf;
    buf = '\0';
  }
  else
    c = getchar();
  return c;
}

/* push character back on input, return 0 on success, or non-zero on fail */
int ungetch(char c) {
  if (buf != '\0') {
    printf("ungetch: too many characters\n");
    return 1;
  }
  buf = c;
  return 0;
}

bool looks_like_math(char s[]) {
  int i;
  for (i = 0; i < MATH_FUNC_AMNT; i++)
    if (MATH_FUNC_NAME[i][0] == s[0] && MATH_FUNC_NAME[i][1] == s[1])
      return true;
  return false;
}

// check if math function operates on one or two arguments
bool is_math_binary(const char math_name[]) {
  return MATH_FUNC_U[
    find_str(math_name, MATH_FUNC_NAME, MATH_FUNC_AMNT)
  ] == NULL;  // looks delicious
}

double do_math(bool is_binary, const char math_name[], double op1, double op2) {
  int math_id;
  double result;

  math_id = find_str(math_name, MATH_FUNC_NAME, MATH_FUNC_AMNT);

  if (is_binary)
    if (math_id == 18)
      result = ldexp(op1, (int)op2);
    else
      result = MATH_FUNC_B[math_id](op1, op2);
  else
    result = MATH_FUNC_U[math_id](op1);

  return result;
}

void set_variable() {
  int c;
  c = getch();
  if (c == EOF) {
    puts("error: variable is EOF");
    return;
  }
  vars[c - 'a'] = pop();
}

void get_variable() {
  int c;
  c = getch();
  if (c == EOF) {
    puts("error: variable is EOF");
    return;
  }
  if (c == '?') {
    push(vars['z'+1-'a']);
    return;
  }
  push(vars[c - 'a']);
}

/* getop: get next character, numeric operand, or a command */
char getop(char s[]) {
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
    else {
      s[1] = getch();
      s[2] = '\0';
      if (looks_like_math(s)) {
        // get the rest of the math func name
        for (i = 2; !isspace(s[i] = getch()); i++);
        ungetch(s[i]);
        s[i] = '\0';
        if (find_str(s, MATH_FUNC_NAME, MATH_FUNC_AMNT) >= 0)
          return MATH;
        else
          printf("we are fucked");
      }
      else {
        ungetch(s[1]);
        s[1] = '\0';
        return c; /* not a number */
      }
    }
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

// skip \n cmd for meta commands
void meta_cmd_skip_nl(void) {
  char c;
  if ((c = getch()) != '\n')
    ungetch(c);
}

void stack_print(void) {
  int i;

  putchar('\t');
  for (i = 0; i < sp; i++)
    printf("%g%s", val[i], i < sp-1 ? ", " : "");
  putchar('\n');
}

void stack_duplicate(void) {
  double op;
  if (sp == 0) {
    puts("error: stack empty");
    return;
  }
  op = pop();
  push(op);
  push(op);
}

void stack_swap(void) {
  double op1, op2;
  if (sp < 2) {
    puts("error: not enough operands on stack");
    return;
  }
  op1 = pop();
  op2 = pop();
  push(op1);
  push(op2);
}

void stack_clear(void) {
  sp = 0;
}

/* reverse Polish calculator */
int main() {
  char c = 0, type = 0;
  double op2 = 0;
  char s[MAXOP] = {0};

  if (!isatty(STDIN_FILENO))
    // find and execute first block like an inline math in latex
    while ((c = getchar()) != MATH_SEP && c != EOF);

  while ((type = getop(s)) != EOF && type != MATH_SEP) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case MATH:
      if (is_math_binary(s)) {
        op2 = pop();
        push(do_math(true, s, pop(), op2));
      } else
        push(do_math(false, s, pop(), 0));
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
    case 'p': // print the stack
      stack_print();
      meta_cmd_skip_nl();
      break;
    case 'd':
      stack_duplicate();
      meta_cmd_skip_nl();
      break;
    case 's':
      stack_swap();
      meta_cmd_skip_nl();
      break;
    case 'c':
      stack_clear();
      meta_cmd_skip_nl();
      break;
    case '=':
      set_variable();
      break;
    case '?':
      get_variable();
      break;
    case '\n':
      vars['z'+1-'a'] = pop();
      printf("\t%.8g\n", vars['z'+1-'a']);
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}
