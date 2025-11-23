#include <stdio.h>

#define LINE_LEN 80

int main() {
  int c;
  int len;
  char line_part[LINE_LEN];

  len = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      if (len == -1)
        putchar('\n');
      len = 0;
      continue;
    }
    if (len > LINE_LEN || len == -1) {
      if (len != -1) {
        line_part[len+1] = '\0';
        len = -1;
        printf("%s", line_part);
      } else {
        putchar(c);
      }
    } else {
      line_part[len] = c;
      ++len;
    }
  }

  return 0;
}
