#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
  int c, nl, nc, nw, state;

  state = OUT;
  nl = nc = nw = 0;
  while((c = getchar()) != EOF) {
    nc++;
    if (c == '\n')
      nl++;
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else if (state == OUT) {
      state = IN;
      nw++;
    }
  }

  printf("lines: %d\n", nl);
  printf("chars: %d\n", nc);
  printf("words: %d\n", nw);
}
