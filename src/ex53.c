#include <stdio.h>
#include <string.h>

#include "lib/myutils.h"

// concatenate t to end of s; s must be big enough
void ch2_strcat(char s[], const char t[]) {
  int i, j;

  i = j = 0;
  while (s[i] != '\0')
    i++;
  while ((s[i++] = t[j++]) != '\0')
    ;
}

// concatenate t to end of s; s must be big enough
void ptr_strcat(char *s, const char *t) {
  while (*s != '\0')
    s++;
  while ((*s++ = *t++));
}

void test_concat(const char *a, const char *b) {
  char ch2[100], ptr[100];

  strcpy(ch2, a);
  strcpy(ptr, a);

  ch2_strcat(ch2, b);
  ptr_strcat(ptr, b);

  if (strcmp(ch2, ptr) == 0)
    printf(GRN "Pass" RST);
  else {
    printf(RED "Fail" RST);
    printf(" : ch2='%s',ptr='%s'", ch2, ptr);
  }
  printf(" : '%s' + '%s'\n", a, b);
}

int main() {
    /* Basic tests */
  test_concat("Hello", " World");
  test_concat("", "Hello");
  test_concat("Hello", "");
  test_concat("", "");

  /* Edge cases */
  test_concat("A", "B");
  test_concat("x", "y");
  test_concat("   ", "   ");

  /* Longer strings */
  test_concat("The quick brown fox", " jumps over the lazy dog");
  test_concat("First part ", "second part");

  /* Special characters */
  test_concat("Count: ", "123!@#");
  test_concat("Hello, ", "World!");

  return 0;
}
