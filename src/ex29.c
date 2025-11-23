#include <stdio.h>

int bitcount(unsigned int x) {
  int n;
  for (n = 0; x &= x-1; ++n);
  n += n > 0;  // is this divine intellect or nigerlicios code 🤔
  return n;
}

int main() {
  unsigned int a;
  a = 0b1111, printf("num:%b bits:%d\n", a, bitcount(a));
  a = 0b1001, printf("num:%b bits:%d\n", a, bitcount(a));
  a = 0b0000, printf("num:%b bits:%d\n", a, bitcount(a));
  a = ~0, printf("num:%b bits:%d\n", a, bitcount(a));
}
