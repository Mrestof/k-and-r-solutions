#include <math.h>
#include <string.h>
#include <stdio.h>
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
  long max_factor = (long)sqrt(num);
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

int getline(char* s, int lim) {
  const char *sc = s;
  int c;

  for (; (c=getchar())!=EOF && c!='\n' && lim > 0; s++, lim--)
    *s = c;
  if (c == '\n' && lim > 0)
    *s++ = c;
  *s = '\0';

  return s - sc;
}

#define ALLOCSIZE 10'000

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free position

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  }
  return NULL;
}

void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

#define MAXLEN 1000 // max length of any input line

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len-1] = '\0'; // delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}
