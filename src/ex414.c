#include <stdio.h>

#define swap(t,x,y) {t tmp; tmp=x; x=y; y=tmp;}

int main() {
  int i1 = 2;
  int i2 = 4;
  printf("%d,%d", i1, i2);
  printf(" -> ");
  swap(int, i1, i2);
  printf("%d,%d\n", i1, i2);

  char c1 = 'k';
  char c2 = 'v';
  printf("%c,%c", c1, c2);
  printf(" -> ");
  swap(char, c1, c2);
  printf("%c,%c\n", c1, c2);

  double d1 = 14.88;
  double d2 = 13.37;
  printf("%g,%g", d1, d2);
  printf(" -> ");
  swap(double, d1, d2);
  printf("%g,%g\n", d1, d2);

  return 0;
}
