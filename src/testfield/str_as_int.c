#include <stdio.h>
#include <string.h>

#include "../lib/myutils.h"

#define BITS_PER_CHAR 8  // you can lower it to 7 and store 9 chars in one long

unsigned long stoi(char *s) {
  unsigned long n = 0;
  int sl = strlen(s) - 1;
  for (int i = 0; i < (int) sizeof(long)*8 / BITS_PER_CHAR; i++) {
    n <<= BITS_PER_CHAR;
    if (i <= sl)
      n |= s[i];
  }
  return n;
}

void itos(char *buf, unsigned long n) {
  int i;
  char nc, *bufi = buf;
  for (i = 0; i < (int) sizeof(long)*8 / BITS_PER_CHAR; i++) {
    nc = n & ((1 << BITS_PER_CHAR) - 1);
    if (nc > 0)
      *bufi++ = nc;
    n >>= BITS_PER_CHAR;
  }
  *bufi = '\0';
  reverse(buf);
}

int strintcmp(unsigned long a, unsigned long b) {
  if (a > b)
    return 1;
  if (a < b)
    return -1;
  return 0;
}

int main() {
  char s1[9] = "secret.1";

  unsigned long n1 = stoi(s1);
  printf("0x%lx\n", n1);

  char sn[9];
  itos(sn, n1);
  printf("%s\n", sn);

  char s2[6] = "aaaaa";
  unsigned long n2 = stoi(s2);
  printf("%d\n", strintcmp(n1, n2));

  char s3[6] = "zzzzz";
  unsigned long n3 = stoi(s3);
  printf("%d\n", strintcmp(n1, n3));

  char s4[9] = "secret.1";
  unsigned long n4 = stoi(s4);
  printf("%d\n", strintcmp(n1, n4));

  unsigned long n5 = n1;
  printf("%d\n", strintcmp(n1, n5));

  return 0;
}
