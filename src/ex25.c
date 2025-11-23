#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Return the first location in a string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2
int any(const char s1[], const char s2[]) {
  int i;
  bool s2_chars[CHAR_MAX+1];

  for (i = 0; i < CHAR_MAX+1; ++i)
    s2_chars[i] = false;

  for (i = 0; s2[i] != '\0'; ++i) {
    if ((unsigned char)s2[i] > CHAR_MAX)
      return -2;
    s2_chars[(unsigned char)s2[i]] = true;
  }

  for (i = 0; s1[i] != '\0'; ++i)
    if ((unsigned char)s1[i] > CHAR_MAX)
      return -3;
    else if (s2_chars[(unsigned char)s1[i]])
      return i;

  return -1;
}

void test_any(const char s1[], const char s2[], int out) {
  int res;

  printf("s1:[%s] s2:[%s]\n", s1, s2);
  fflush(stdout);
  res = any(s1, s2);
  if (res < -1) {
    printf(ANSI_COLOR_RED "Error[res=%d]" ANSI_COLOR_RESET "\n", res);
  }
  else if (res == out) {
    printf(ANSI_COLOR_GREEN "out:[%d]" ANSI_COLOR_RESET "\n", res);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%d]" ANSI_COLOR_RESET "\n", out);
    printf(ANSI_COLOR_YELLOW "act_out:[%d]" ANSI_COLOR_RESET "\n", res);
  }
}

int main() {
  // Simple match in middle
  test_any("hello", "e", 1);
  // First char matches
  test_any("hello", "h", 0);
  // Match with multiple candidates in s2 – earliest in s1 wins 'e' at 1, 'o'
  // at 4 → expect 1
  test_any("hello", "oxez", 1);
  // No common chars → -1
  test_any("abcdef", "XYZ", -1);
  // s2 has many chars, only one at end of s1 'f' at index 5
  test_any("abcdef", "qrf", 5);
  // s2 has duplicates, should not affect result 'b' at index 1
  test_any("abcabc", "bbbbb", 1);
  // First char appears several times, but earliest index used 'a' at 1
  test_any("banana", "az", 1);
  // Case sensitivity: 'a' != 'A' no match → -1
  test_any("abc", "XYZA", -1);
  // Case sensitivity: match with same case 'A' at 0
  test_any("AbC", "xAy", 0);
  // Empty s1 → no match
  test_any("", "abc", -1);
  // Empty s2 → no chars to match → always -1
  test_any("abc", "", -1);
  // Spaces and punctuation space at index 3
  test_any("hi, there", " ", 3);
  // Match is not the earliest *in s2* but earliest in s1 s1: "xyzabc", s2:
  // "cx" → 'x' at 0, 'c' at 5 → expect 0
  test_any("xyzabc", "cx", 0);
  // All matchable chars, but earliest is in the middle s1: "0123456789", s2:
  // "975" → '5' at 5
  test_any("0123456789", "975", 5);

  test_any("привет мир", "в", 3);
  test_any("💀😄💀😄", "💀", 0);
  return 0;
}
