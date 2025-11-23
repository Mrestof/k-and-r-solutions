#include <stdio.h>


// x=
// xxxxxx
// y=
// yyy110
// n=p=3
// r=
// xx110x
//
// xxxxxx
// yyy110<<p+1-n
//
// 111111<<p+1
// 110000~
// 001111
//
// yy1100
// &
// 001111
// =
// 001100
//
// xxxxxx&110001
// 001100
//
// xx000x
// |
// 001100
// =
// xx110x
//
// n=p=3
// r=
// 110001
//
// 111111<<p+1
// 110000
//
// NOTE: this is probably a better option on creating the mask for x
// 111111<<n
// 111000~
// 000111<<p+1-n
// 001110~
// 110001
//
// 111111<<p+1-n
// 111110~
// 000001
//
// 110000
// |
// 000001
// =
// 110001


// return x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged
//
// x=100000 n=3 p=3 y=000110 => 101100
unsigned int setbits(unsigned int x, int p, int n, int y) {
  return (
    (
      (y << (p+1-n)) &
      (~(~0u << (p+1)))
    ) |
    (
      x &
      (
        (~0u << (p+1)) |
        (~(~0u << (p+1-n)))
      )
    )
  );
}

int main() {
  printf("%b\n", setbits(0b100000, 3, 3, 0b000110));
  printf("%b\n", setbits(0b000000, 5, 1, 0b000001));
  putchar('\n');
  printf("%b\n", setbits(0b100000, 3, 3, 0b110110));
  printf("%b\n", setbits(0b000000, 5, 1, 0b011101));
  putchar('\n');
  printf("%b\n", setbits(0b100000, 5, 6, 0b110101));
  putchar('\n');
  printf("%b\n", setbits(0b111011, 3, 3, 0b000110));
}
