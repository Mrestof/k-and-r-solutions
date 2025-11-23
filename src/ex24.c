#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define CHAR_AMNT 128
#define MAX_INPUT 100

// Delete each character in s1 that matches any character in the string s2
int squeeze(char s1[], const char s2[]) {
  int i, j;
  bool s2_chars[CHAR_AMNT];

  for (i = 0; i < CHAR_AMNT; ++i)
    s2_chars[i] = false;

  for (i = 0; s2[i] != '\0'; ++i) {
    if ((unsigned char)s2[i] > 127)
      return 1;
    s2_chars[(unsigned char)s2[i]] = true;
  }

  for (i = j = 0; s1[j] != '\0'; ++j) {
    if ((unsigned char)s2[i] > 127)
      return 2;
    if (!s2_chars[(unsigned char)s1[j]])
      s1[i++] = s1[j];
  }
  s1[i] = '\0';
  return 0;
}

void test_squeeze(const char s1[], const char s2[], const char out[]) {
  char input[MAX_INPUT];
  int res;
  strcpy(input, s1);

  printf("s1:[%s] s2:[%s]\n", s1, s2);
  fflush(stdout);
  res = squeeze(input, s2);
  if (res != 0) {
    printf(ANSI_COLOR_YELLOW "Error[res=%d]" ANSI_COLOR_RESET "\n", res);
  }
  else if (strcmp(input, out) == 0) {
    printf(ANSI_COLOR_GREEN "out:[%s]" ANSI_COLOR_RESET "\n", input);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%s]" ANSI_COLOR_RESET "\n", out);
    printf(ANSI_COLOR_YELLOW "act_out:[%s]" ANSI_COLOR_RESET "\n", input);
  }
}

int main() {
  test_squeeze("hello world","lo","he wrd");
  test_squeeze("привет мир", "ри", "пвет м");
  test_squeeze("banana","an","b");
  test_squeeze("abcdef","xyz","abcdef");
  test_squeeze("abcdef","ace","bdf");
  test_squeeze("aaaaaa","a","");
  test_squeeze("test123","13","test2");
  test_squeeze("foo bar"," ","foobar");
  test_squeeze("foo bar","o ","fbar");
  test_squeeze("!!!???","!","???");
  test_squeeze("!!!???","!?","");
  test_squeeze("1234567890","02468","13579");
  test_squeeze("UPPERlower","Ue","PPERlowr");
  test_squeeze("UPPERlower","UPPER","lower");
  test_squeeze("UPPERlower","lower","UPPER");
  test_squeeze("","abc","");
  test_squeeze("abc","", "abc");
  test_squeeze("same","same","");
  test_squeeze("💀😄💀😄","💀","😄😄");         // works if bytes preserved
  return 0;
}
