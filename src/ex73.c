// SKIP: just write the same code as in the book to
// better memorize how to work with `...`

#include <stdarg.h>
#include <stdio.h>

void minprintf(char* fmt, ...) {
  va_list ap;
  char *p, *sval;
  int ival;
  double dval;

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
      case 'd':
        ival = va_arg(ap, int);
        printf("%d", ival);
        break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
        break;
      case 's':
        sval = va_arg(ap, char*);
        printf("%s", sval);
        break;
      default:
        putchar(*p);
        break;
    }
  }
}

int main(void) {
  // sanity checks
  minprintf("num: %d\n", 0);
  minprintf("num: %d\n", -1);
  minprintf("num: %d\n", +1);
  minprintf("num: %d\n", 182398);

  minprintf("float: %f\n", .51);
  minprintf("float: %f\n", 355./113.);

  minprintf("str: %s\n", "some string");
  minprintf("str: %s\n", "");
  minprintf("str: %s\n", "wassup nwords");

  return 0;
}
