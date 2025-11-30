#include <math.h>
#include <string.h>
#include "myutils.h"

unsigned long next = 1;

int my_rand(void) {
  next = next * 1103515245 + 13245;
  return (unsigned int)(next/65536) % 32768;
}

void my_srand(unsigned long seed) {
  next = seed;
}

bool is_prime(long num) {
  if (num < 2) return false;
  long max_factor = sqrt(num);
  for (long a = 2; a <= max_factor; a++)
    if (num % a == 0) return false;
  return true;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void reverse(char s[]) {
  int i, j;
  char c;

  for (j = 0; s[j] != '\0'; ++j);
  --j;

  for (i = 0; i < j; ++i, --j) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

int find_str(const char s[], char * const in[], const int in_len) {
  int i;

  for (i = 0; i < in_len; i++)
    if (strcmp(s, in[i]) == 0)
      return i;

  return -1;
}
