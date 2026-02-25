#include <stdio.h>

#define MAXLINE 1'000

bool diff(char *l1, char* l2) {
  return false;
}

int main(int argc, char* argv[]) {
  FILE *f1, *f2;
  char l1[MAXLINE], l2[MAXLINE];

  if (argc != 3)
    return 3;

  f1 = fopen(argv[1], "r");
  f2 = fopen(argv[2], "r");

  if (f1 == NULL || f2 == NULL)
    return 2;

  while (!feof(f1) && !feof(f2)) {
    if (
      fgets(l1, MAXLINE, f1) == NULL
      || fgets(l2, MAXLINE, f2) == NULL
    )
      return 4;
    if (!diff(l1, l2))
      continue;
    printf("< %s\n", l1);
    printf("> %s\n", l2);
    return 1;
  }

  return 0;
}
