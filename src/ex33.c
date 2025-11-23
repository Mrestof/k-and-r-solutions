#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool expandable(char l, char r) {
  if (l >= 'a' && l <= 'z' && r >= 'a' && r <= 'z' && r > l) return true;
  if (l >= 'A' && l <= 'Z' && r >= 'A' && r <= 'Z' && r > l) return true;
  if (l >= '0' && l <= '9' && r >= '0' && r <= '9' && r > l) return true;
  return false;
}

void expand(char buf[], const char inp[]) {
  int i, j;
  char c;

  for (i = j = 0; inp[i] != '\0'; ++i) {
    if (
      inp[i] == '-' && i > 0 && inp[i+1] != '\0'
      && expandable(inp[i-1], inp[i+1])
    )
      for(c = inp[i-1] + 1; c < inp[i+1]; ++c, ++j)
        buf[j] = c;
    else
      buf[j++] = inp[i];
  }
  buf[j] = '\0';
}

void test_expand(const char inp[], const char sol[]) {
  char buf[256];

  printf("inp:[%s]\n", inp);
  fflush(stdout);
  expand(buf, inp);
  if (strcmp(buf, sol) == 0) {
    printf(ANSI_COLOR_GREEN "out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
  else {
    printf(ANSI_COLOR_YELLOW "exp_out:[%s]" ANSI_COLOR_RESET "\n", sol);
    printf(ANSI_COLOR_YELLOW "act_out:[%s]" ANSI_COLOR_RESET "\n", buf);
  }
}

int main() {
  // owo lowercase catwalk
  test_expand("a-z", "abcdefghijklmnopqrstuvwxyz");

  // uwu uppercase runway
  test_expand("A-Z", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  // digit parade nya
  test_expand("0-9", "0123456789");

  // chained spans meow
  test_expand("a-b-c", "abc");

  // mix letters + nums, mwah :3
  test_expand("a-d0-3", "abcd0123");

  // invalid wange stays litewal nya~
  test_expand("z-a", "z-a");

  // weading dash snuggled
  test_expand("-a-z", "-abcdefghijklmnopqrstuvwxyz");

  // twailing dash cuddled
  test_expand("a-z-", "abcdefghijklmnopqrstuvwxyz-");

  // doppio hyphen uwu
  test_expand("a-a-z", "a-abcdefghijklmnopqrstuvwxyz");

  // no hyphen? no expwansion :3
  test_expand("abopqr", "abopqr");

  // mix cases, stiww kawai
  test_expand("A-Fg-l", "ABCDEFghijkl");

  // ovewlapping digits nya
  test_expand("0-90-5", "0123456789012345");

  // wange hugging witeral 5
  test_expand("5-855-8", "567855678");

  // multi mini spans meow
  test_expand("a-ce-g", "abcefg");

  // scweaming case sep pawths
  test_expand("a-bC-Dx-z", "abCDxyz");

  // hyphen cuddle pawty
  test_expand("--", "--");

  // lone trailing dash uwu
  test_expand("m-", "m-");

  // lone weading dash mew
  test_expand("-n", "-n");

  // digits then litewal 0 nya
  test_expand("0-90", "01234567890");

  // big triple wibbon
  test_expand("a-za-za-z", "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

  return 0;
}
