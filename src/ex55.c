#include <stdio.h>
#include <string.h>

#include "lib/myutils.h"

// SHOULD BEHAVE THE SAME AS `strncpy` FROM <string.h>
// copy at most n characters of string ct to s; return s. Pad with '\0''s if ct
// has fewer than n characters.
char* strncpy_kr(char *s, const char *ct, unsigned long n) {
  char *sc = s;
  for (; n; n--) {
    if (!*ct)
      break;
    *sc++ = *ct++;
  }
  for (; n; n--)
    *sc++ = '\0';
  return s;
}

// SHOULD BEHAVE THE SAME AS `strncat` FROM <string.h>
// concatenate at most n characters of string ct to string s, terminate s with
// '\0'; return s.
char* strncat_kr(char *s, const char *ct, unsigned long n) {
  char *sc = s;
  while (*sc)
    sc++;
  for (; n; n--) {
    if (!*ct)
      break;
    *sc++ = *ct++;
  }
  *sc = '\0';
  return s;
}

// SHOULD BEHAVE THE SAME AS `strncmp` FROM <string.h>
// compare at most n characters of string cs to string ct; return <0 if cs<ct, 0
// if cs==ct, or >0 if cs>ct.
int strncmp_kr(const char *cs, const char *ct, unsigned long n) {
  if (n == 0)
    return 0;
  for (; n-1; n--) {
    if (*cs != *ct || !*cs || !*ct)
      break;
    cs++;
    ct++;
  }
  return *cs - *ct;
}

void test_strncpy(const char *s, const char *t, unsigned long n) {
  char og[100];
  char kr[100];
  strcpy(og, s);
  strcpy(kr, s);
  strncpy(og, t, n);
  strncpy_kr(kr, t, n);
  if (strcmp(og, kr) == 0)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(" : s='%s',t='%s',n='%lu',og='%s',kr='%s'" RST "\n", s, t, n, og, kr);
}

void test_strncat(const char *s, const char *t, unsigned long n) {
  char og[100];
  char kr[100];
  strcpy(og, s);
  strcpy(kr, s);
  strncat(og, t, n);
  strncat_kr(kr, t, n);
  if (strcmp(og, kr) == 0)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(" : s='%s',t='%s',n='%lu',og='%s',kr='%s'" RST "\n", s, t, n, og, kr);
}

void test_strncmp(const char *s, const char *t, unsigned long n) {
  int og;
  int kr;
  og = strncmp(s, t, n);
  kr = strncmp_kr(s, t, n);
  if (og == kr)
    printf(GRN "Pass");
  else
    printf(RED "Fail");
  printf(" : s='%s',t='%s',n='%lu',og='%d',kr='%d'" RST "\n", s, t, n, og, kr);
}

int main() {
  /* STRNCPY Tests (this one was weird, so more tests for it just in case) */
  printf("--- strncpy tests ---\n");
  /* Edge cases with exact boundaries */
  test_strncpy("abcde", "12345", 5);      /* Exact replacement, same length */
  test_strncpy("abcde", "123456789", 5);  /* Exact replacement, source longer */
  test_strncpy("abcde", "123", 5);        /* Replacement with padding */
  /* Zero and single character cases */
  test_strncpy("test", "x", 0);           /* Copy zero characters */
  test_strncpy("test", "x", 1);           /* Copy single character */
  test_strncpy("a", "b", 1);              /* Single char to single char */
  test_strncpy("", "a", 1);               /* Copy to empty string */
  /* Padding scenarios */
  test_strncpy("hello", "a", 3);          /* Short source, lots of padding */
  test_strncpy("hello", "ab", 5);         /* Source shorter, pad to end */
  test_strncpy("hello", "", 2);           /* Empty source, pad everything */
  test_strncpy("hello", "x", 1);          /* Minimal padding case */
  /* Boundary testing with different lengths */
  test_strncpy("1234567890", "abc", 3);   /* Short replacement in long string */
  test_strncpy("1234567890", "abc", 7);   /* Short with heavy padding */
  test_strncpy("abc", "1234567890", 3);   /* Long source, exact boundary */
  test_strncpy("abc", "1234567890", 2);   /* Long source, truncated */
  /* Special character cases */
  test_strncpy("hello", "tab\there", 4);  /* Tab character */
  //test_strncpy("hello", "new\nline", 5);  /* Newline character */
  test_strncpy("hello", "quote\"test", 6); /* Quote character */
  test_strncpy("hello", "back\\slash", 7); /* Backslash */
  /* Numeric and mixed content */
  test_strncpy("hello", "12345", 3);      /* Numbers, partial */
  test_strncpy("12345", "abcde", 5);      /* Letters replace numbers */
  test_strncpy("test", "123", 4);         /* Numbers with padding */
  test_strncpy("abc123", "xyz", 3);       /* Mixed content replacement */
  /* Longer string scenarios */
  test_strncpy("The quick brown fox", "REPLACED", 8);
  test_strncpy("short", "This is a very long replacement string", 10);
  test_strncpy("destination", "src", 5);
  test_strncpy("original content here", "new", 3);
  /* Repeated character patterns */
  test_strncpy("aaaaa", "bbb", 3);        /* Replace with different char */
  test_strncpy("aaaaa", "bbb", 5);        /* Replace with padding */
  test_strncpy("abcde", "xxxxx", 3);      /* Partial repeated replacement */
  test_strncpy("test", "aaaaaaaaaa", 4);  /* Long repeated source */
  /* Mixed length edge cases */
  test_strncpy("a", "bcdefghijk", 1);     /* Single char dest, long source */
  test_strncpy("ab", "cdefghijk", 2);     /* Short dest, long source */
  test_strncpy("abcdefghijk", "xy", 2);   /* Long dest, short replacement */
  test_strncpy("abcdefghijk", "xy", 8);   /* Long dest, short with padding */
  /* Punctuation and symbols */
  test_strncpy("hello", "!@#$%", 3);      /* Special symbols */
  test_strncpy("test", "()[]", 4);        /* Brackets */
  test_strncpy("orig", "+-*/", 3);        /* Math operators */
  test_strncpy("data", ".,;:", 2);        /* Punctuation */
  /* Space handling */
  test_strncpy("hello", "   ", 3);        /* All spaces */
  test_strncpy("hello", " a ", 3);        /* Spaces around letter */
  test_strncpy("nospace", "has space", 5); /* Insert spaces */
  test_strncpy("   ", "abc", 3);          /* Replace spaces */
  /* Large n values (testing padding behavior) */
  test_strncpy("test", "a", 10);          /* Heavy padding */
  test_strncpy("test", "ab", 15);         /* Extreme padding */
  test_strncpy("x", "y", 20);             /* Single char with lots of padding */


  /* STRNCAT Tests */
  printf("--- strncat tests ---\n");
  test_strncat("hello", " world", 6);      /* Full append */
  test_strncat("hello", " world", 3);      /* Partial append */
  test_strncat("hello", " world", 0);      /* Zero append */
  test_strncat("", "hello", 5);            /* Empty dest */
  test_strncat("hello", "", 3);            /* Empty source */
  test_strncat("abc", "d", 1);             /* Single char */
  test_strncat("file", ".txt", 4);         /* Extension */
  test_strncat("Count: ", "123456", 3);    /* Partial number */
  test_strncat("start", "end", 10);        /* n > source length */
  test_strncat("base", "extension", 3);    /* Partial extension */
  test_strncat("path/", "file.txt", 8);    /* Path concat */
  test_strncat("Hello", "!", 1);           /* Punctuation */

  /* STRNCMP Tests */
  printf("--- strncmp tests ---\n");
  test_strncmp("hello", "hello", 5);       /* Equal strings */
  test_strncmp("hello", "help", 3);        /* Equal prefix */
  test_strncmp("abc", "abd", 3);           /* First < second */
  test_strncmp("abd", "abc", 3);           /* First > second */
  test_strncmp("abc", "abcd", 4);          /* First shorter */
  test_strncmp("abcd", "abc", 4);          /* First longer */
  test_strncmp("", "", 5);                 /* Both empty */
  test_strncmp("hello", "", 3);            /* Second empty */
  test_strncmp("", "hello", 3);            /* First empty */
  test_strncmp("same", "same", 0);         /* Zero comparison */
  test_strncmp("Hello", "hello", 5);       /* Case difference */
  test_strncmp("abc", "abc", 2);           /* Partial equal */
  test_strncmp("world", "hello", 1);       /* Different first char */
  test_strncmp("test", "text", 3);         /* Different middle */

  return 0;
}
