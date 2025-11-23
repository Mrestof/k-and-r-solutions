#include <math.h>
#include "myutils.h"

unsigned long next = 1;

int my_rand(void) {
  next = next * 1103515245 + 13245;
  return (unsigned int)(next/65536) % 32768;
}

void my_srand(unsigned long seed) {
  next = seed;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

bool is_prime(long num) {
  if (num < 2) return false;
  long max_factor = sqrt(num);
  for (long a = 2; a <= max_factor; a++)
    if (num % a == 0) return false;
  return true;
}
