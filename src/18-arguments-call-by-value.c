#include <stdio.h>

int power(int m, int n);

int main() {
  int i;

  for (i = 0; i < 10; ++i)
    printf("%d %3d %6d\n", i, power(2,i), power(-3,i));
  return 0;
}

int power(int m, int n) {
  int p;

  for (p = 1; n > 0; --n)
    p = p * m;
  return p;
}
