#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void escape(char buf[], const char inp[]) {
  int i, ofs;
  for (i = ofs = 0; inp[i] != '\0'; ++i) {
    switch (inp[i]) {
      case '\n':
        buf[i+ofs] = '\\';
        ++ofs;
        buf[i+ofs] = 'n';
        break;
      case '\t':
        buf[i+ofs] = '\\';
        ++ofs;
        buf[i+ofs] = 't';
        break;
      default:
        buf[i+ofs] = inp[i];
        break;
    }
  }
  buf[i+ofs] = '\0';
}

void rescape(char buf[], const char inp[]) {
  int i, ofs;
  char c;
  for (i = ofs = 0; (c = inp[i+ofs]) != '\0'; ++i) {
    switch (inp[i+ofs]) {
      case '\\':
        switch (inp[i+ofs+1]) {
          case 'n':
            ++ofs;
            c = '\n';
            break;
          case 't':
            ++ofs;
            c = '\t';
            break;
        }
        break;
    }
    buf[i] = c;
  }
  buf[i] = '\0';
}

void test_escape(const char inp[], const char sol[]) {
  char buf[256];

  printf("inp:[%s]\n", inp);
  fflush(stdout);
  escape(buf, inp);
  if (strcmp(buf, sol) == 0) {
    printf(ANSI_COLOR_GREEN "out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%s]" ANSI_COLOR_RESET "\n", sol);
    printf(ANSI_COLOR_YELLOW "act_out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
}

void test_rescape(const char inp[], const char sol[]) {
  char buf[256];

  printf("inp:[%s]\n", inp);
  fflush(stdout);
  rescape(buf, inp);
  if (strcmp(buf, sol) == 0) {
    printf(ANSI_COLOR_GREEN "out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%s]" ANSI_COLOR_RESET "\n", sol);
    printf(ANSI_COLOR_YELLOW "act_out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
}

int main() {
  printf("\n= test escape =\n");

  /* 1. Empty string */
  test_escape("", "");

  /* 2. No escapable chars (identity) */
  test_escape("hello, world", "hello, world");

  /* 3. Single newline */
  test_escape("a\nb", "a\\nb");

  /* 4. Single tab */
  test_escape("a\tb", "a\\tb");

  /* 5. Multiple newlines & tabs mixed */
  test_escape(
    "line1\nline2\tend\n",
    "line1\\nline2\\tend\\n"
  );

  /* 6. String that is only control chars */
  test_escape("\n\t\n", "\\n\\t\\n");

  /* 9. Leading and trailing escapable chars */
  test_escape(
    "\nhello\t",
    "\\nhello\\t"
  );

  /* 10. Long-ish string with many escapables */
  test_escape(
    "a\nb\tc\n\td",
    "a\\nb\\tc\\n\\td"
  );


  printf("\n= test rescape =\n");

  // 13) Empty string
  test_rescape("", "");

  // 1) No escapes
  test_rescape("hello", "hello");

  // 2) Single newline escape
  test_rescape("\\n", "\n");

  // 3) Single tab escape
  test_rescape("\\t", "\t");

  // 4) Newline in the middle
  test_rescape("line1\\nline2", "line1\nline2");

  // 5) Tab in the middle
  test_rescape("col1\\tcol2", "col1\tcol2");

  // 6) Mixed \\n and \\t
  test_rescape("a\\n\\tb", "a\n\tb");

  // 7) Multiple escapes separated by text
  test_rescape("x\\ny\\nz", "x\ny\nz");

  // 8) Literal backslash not forming escape (\\x)
  test_rescape("\\x", "\\x");

  // 10) Escaped newline after literal backslash
  // input chars: '\\' '\\' 'n' 'x' → output: '\' '\n' 'x'
  test_rescape("\\\\nx", "\\\nx");

  // 11) Trailing backslash at end of string
  // depending on implementation, usually copied as-is
  test_rescape("abc\\", "abc\\");

  // 14) Only spaces and escapes
  test_rescape(" \\n \\t ", " \n \t ");
}
