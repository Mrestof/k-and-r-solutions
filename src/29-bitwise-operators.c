#include <stdio.h>

unsigned int getbits(unsigned int x, int p, int n) {
  return (x >> (p+1-n)) & ~(~0u << n);
}

int main() {
  printf("%b\n", getbits(0b1011100, 4, 3));
}
