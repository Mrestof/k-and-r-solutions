#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../lib/myutils.h"

void test_find_str() {
  int i;
  char *arr[4] = {"reimu", "miku", "rin", "teto"};
  i = find_str("miku", arr, 4);
  printf("miku: %d\n", i);
  i = find_str("reimu", arr, 4);
  printf("reimu: %d\n", i);
  i = find_str("rin", arr, 4);
  printf("rin: %d\n", i);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wstring-plus-int"
void test_string_literal_pointers() {
  printf("%s\n", "hello world" + 6);
  printf("%s\n", &"hello world"[6]);
  printf("%s\n", &6["hello world"]);

  char *c = "test";
  printf("%ld\n", c);
  printf("%ld\n", c+1);
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-overflow"
void test_null_pointer() {
  printf("%s \n", NULL);
  printf("%d \n", NULL);
  printf("%c \n", NULL);
}
#pragma GCC diagnostic pop

void func_accepts_array(const char a[]) {
  //a[0] = 'a';  (can't do this)
  a = "ab";
  printf("%s\n", a);
}

void test_declarations() {
  func_accepts_array("test");
}

void test_overflow() {
  signed int a;
  for (a = 1; a + 1 > a; ++a);
  printf("%d\n", a);
}

void test_isgraph() {
  char c;

  for (c = 0; c < 127; ++c) {
    printf("%d:\t%d\n", c, isgraph(c)>0);
  }
}

void sizeof_stuff() {
  printf("bool: %ld\n", sizeof(_Bool));
  printf("int: %ld\n", sizeof(int));
}

void funny_chars() {
  printf("%d\n", '2' - '0');
}

void test_is_prime() {
  printf("primes found: ");
  bool delim = false;
  for (int i = 1; i <= 30; i++) {
    if (is_prime(i)) {
      printf("%c%d", delim? ',': '\0', i);  // is this nigerlicious or divine intellect?
      delim = true;
    }
  }
}

void test_swap() {
  int a = 2, b = 3;
  printf("a:%i, b:%i\n", a, b);
  swap(&a, &b);
  printf("a:%i, b:%i", a, b);
}

int main() {
  test_find_str();
  return 0;
}
