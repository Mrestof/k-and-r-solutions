#include <stdio.h>

// count lines in input
int main() {
  int c, bc, tc, nlc;

  bc = 0;
  tc = 0;
  nlc = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++bc;
    if (c == '\t')
      ++tc;
    if (c == '\n')
      ++nlc;
  }
  printf("blanks: %d\n", bc);
  printf("tabs: %d\n", tc);
  printf("newlines: %d\n", nlc);
}
