#include <stdarg.h>
#include <stdio.h>

int p(char * prefix, char* fmt, ...) {
  int rc;
  va_list ap;
  va_start(ap, fmt);

  printf("%s", prefix);
  rc = vprintf(fmt, ap);

  va_end(ap);
  return rc;
}

char C[] = "some prefix | ";

int main(void) {
  p(C, "%s: %g", "pi", 355./113.);
  return 0;
}
