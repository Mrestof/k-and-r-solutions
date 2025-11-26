#include <stdio.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int strindex(const char s[], const char t[]) {
  int i, j, k;
  int res = -1;

  for (i = 0; s[i] != '\0'; i++) {
    for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      res = i;
  }

  return res;
}

void test_strindex(const char s[], const char t[], const int sol) {
  int out;

  printf("s:[%s] t:[%s]\n", s, t);
  fflush(stdout);

  out = strindex(s, t);

  if (out == sol) {
    printf(ANSI_COLOR_GREEN "out:[%d]" ANSI_COLOR_RESET "\n", sol);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%d]" ANSI_COLOR_RESET "\n", sol);
    printf(ANSI_COLOR_YELLOW "act_out:[%d]" ANSI_COLOR_RESET "\n", out);
  }
}

int main() {
  // manual
  test_strindex("some uno dos uno wow", "uno", 13); // simple test
  test_strindex("some uno dos uno una", "uno", 13); // complete pattern test

  // ai
  test_strindex("hello kitty", "kitty", 6);         // match late
  test_strindex("abcabcabc", "abc", 6);             // last abc
  test_strindex("abcabcabc", "cab", 5);             // overlap
  test_strindex("uwu owo", "owo", 4);               // ending hit
  test_strindex("meow meow", "purr", -1);           // no match
  test_strindex("aaaaa", "aa", 3);                  // repeated overlap
  test_strindex("", "hi", -1);                      // empty haystack
  test_strindex("nyanyaa", "", -1);                 // empty needle
  test_strindex("case sensitivity", "Case", -1);    // verify lowercase only
  test_strindex("arch pride", "arch", 0);           // prefix

  return 0;
}
