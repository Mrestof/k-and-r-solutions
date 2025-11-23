#include <stdio.h>

// x=
// 110110
// n=2
// r=
// 101101
//
// 001101 =x1
// |
// 100000 =x2
// =
// 101101 =r
//
// 110110>>n
// 001101 =x1
//
// 110110<<6-n
// 100000 =x2

// return the value of the integer x rotated to the right by n positions
//
// x=100101 n=3 p=3 => 101110
unsigned int invert(unsigned int x, int n) {
  n %= sizeof(x)*8;
  return (
    (x << (sizeof(x)*8 - n))
    |
    (x >> n)
  );
}

int main() {
  printf("p:%d \torg:%b\n", 1, 0x80000005);
  printf("     \trot:%b\n", invert(0x80000005, 1));
  putchar('\n');
  printf("p:%d \torg:%b\n", 12, 0x80005fb7);
  printf("     \trot:%b\n", invert(0x80005fb7, 12));
  putchar('\n');
  printf("p:%d \torg:%b\n", 32, 0x800eeeee);
  printf("     \trot:%b\n", invert(0x800eeeee, 32));
  putchar('\n');
  printf("p:%d \torg:%b\n", 36, 0x800eeeee);
  printf("     \trot:%b\n", invert(0x800eeeee, 36));
  putchar('\n');
  printf("p:%d \torg:%b\n", 42, 0x800eeeee);  // 42 % 32 = 10
  printf("     \trot:%b\n", invert(0x800eeeee, 42));
}
