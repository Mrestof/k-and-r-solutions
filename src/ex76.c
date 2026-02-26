#include <stdio.h>

#define MAXLINE 1'000

bool diff(char *l1, char* l2) {
  while (*l1 && *l1 == *l2)
    l1++, l2++;
  return *l1 != *l2;
}

int main(int argc, char* argv[]) {
  FILE *f1, *f2;
  char l1[MAXLINE], l2[MAXLINE];
  char *r1, *r2;

  if (argc != 3)
    return 3;

  f1 = fopen(argv[1], "r");
  f2 = fopen(argv[2], "r");

  if (f1 == NULL || f2 == NULL)
    return 2;

  for (;;) {
    r1 = fgets(l1, MAXLINE, f1);
    r2 = fgets(l2, MAXLINE, f2);
    if (!r1 || !r2)
      break;
    if (diff(l1, l2)) {
      printf("< %s", l1);
      printf("> %s", l2);
      return 1;
    }
  }

  if (feof(f1) != feof(f2)) {
    if (feof(f1))
      printf("> %s", l2);
    if (feof(f2))
      printf("< %s", l1);
    return 1;
  }

  return 0;
}
