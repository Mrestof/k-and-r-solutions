#include <stdio.h>

#include "lib/myutils.h"

bool strend(const char *s, const char *t) {
  int cnt = 2;  // uhm, the algo sucks a little, so here's a magic fix

  if (!*t)
    return true;
  if (!*s)
    return false;

  while (*++s);
  while (*++t)
    cnt++;

  for (; cnt; cnt--)
    if (*t-- != *s--)
      return false;

  return true;
}

void test_strend(const char *s, const char *t, const bool exp) {
  bool act = strend(s, t);
  if (act == exp)
    printf(GRN "Pass" RST);
  else {
    printf(RED "Fail" RST);
    printf(" (exp=%d,act=%d)'", exp, act);
  }
  printf(" : s='%s',t='%s'\n", s, t);
}

int main() {
  // Basic cases
  test_strend("hello", "lo", true);
  test_strend("hello", "he", false);
  test_strend("world", "ld", true);
  test_strend("world", "wo", false);
  test_strend("test", "test", true);

  // Empty strings
  test_strend("hello", "", true);
  test_strend("", "", true);
  test_strend("", "x", false);

  // Single characters
  test_strend("hello", "o", true);
  test_strend("x", "x", true);
  test_strend("a", "b", false);

  // Suffix longer than string
  test_strend("hi", "hello", false);
  test_strend("a", "abc", false);

  // Tricky cases
  test_strend("hello", "llo", true);
  test_strend("hello", "llox", false);
  test_strend("abcabc", "abc", true);
  test_strend("abcabc", "cab", false);

  // Case sensitivity
  test_strend("Hello", "Lo", false);
  test_strend("Test", "st", true);
  test_strend("Test", "ST", false);

  // Special characters
  test_strend("file.txt", ".txt", true);
  test_strend("file.cpp", ".txt", false);
  test_strend("hello!", "!", true);
  test_strend("hello world", "world", true);

  // Numbers
  test_strend("version1.0", "1.0", true);
  test_strend("test123", "23", true);
  test_strend("test123", "13", false);

  // Longer strings
  test_strend("The quick brown fox jumps", "jumps", true);
  test_strend("The quick brown fox jumps", "fox", false);

  // Repeated patterns
  test_strend("testing", "ing", true);
  test_strend("testing", "nesting", false);
  test_strend("aaaaaa", "aa", true);
  test_strend("ababab", "bab", true);

  return 0;
}
