#include <stdio.h>

// x=
// xxxxxx
// n=p=3
// r=
// xxrrrx
//
// xx000x
// 00rrr0
//
// m=
// 111111<<p
// 111000~
// 000111<<p+1-n
// 001110
//
// xxxxxx
// &
// 001110~
// 110001
// =
// xx000x
//
// xxxxxx~
// rrrrrr
// &
// 001110
// =
// 00rrr0

// p=6 n=1
//
// m=
// 11111111111111<<n
// 11111111111110~
// 00000000000001<<p+1-n
// 00111111000000

// return x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged
//
// x=100000 n=3 p=3 => 101110
unsigned int invert(unsigned int x, int p, int n) {
  unsigned int m = ~(~0u << n) << (p+1-n);
  return (
    (x & ~m)
    |
    (~x & m)
  );
}

int main() {
  printf("p:%d n:%d\torg:%b\n", 3, 3, 0b100000);
  printf("         \tinv:%b\n", invert(0b100000, 3, 3));
  printf("p:%d n:%d\torg:%b\n", 3, 3, 0b101010);
  printf("         \tinv:%b\n", invert(0b101010, 3, 3));
  printf("p:%d n:%d\torg:%b\n", 5, 1, 0b100000);
  printf("         \tinv:%b\n", invert(0b100000, 5, 1));
  printf("p:%d n:%d\torg:%b\n", 5, 6, 0b000000);
  printf("         \tinv:%b\n", invert(0b000000, 5, 6));
  putchar('\n');
  printf("p:%d n:%d\torg:%b\n", 5, 1, 0xffffffff);
  printf("         \tinv:%b\n", invert(0xffffffff, 5, 1));
  printf("p:%d n:%d\torg:%b\n", 5, 6, 0xffffffff);
  printf("         \tinv:%b\n", invert(0xffffffff, 5, 6));
  printf("p:%d n:%d\torg:%b\n", 24, 18, 0xffffffff);
  printf("         \tinv:%b\n", invert(0xffffffff, 24, 18));
}
