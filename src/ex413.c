#include <stdio.h>
#include <string.h>

#define MAXSTRLEN 1000

void reverse_rec(char s[], int i, int slen) {
  if (i > slen/2)
    return;
  char c = s[i];
  s[i] = s[slen-i-1];
  s[slen-i-1] = c;
  reverse_rec(s, i+1, slen);
}

void reverse(char s[]) {
  int i;
  for (i = 0; s[i] != '\0'; i++);
  reverse_rec(s, 0, i);
}

void test_reverse(const char inp[]) {
  char out[MAXSTRLEN];
  strcpy(out, inp);
  reverse(out);
  printf("%s -> %s\n", inp, out);
}

int main() {
  test_reverse("12345");
  test_reverse("some string");
  return 0;
}
