#include <stdio.h>
#include <limits.h>

void print_constants() {
  printf("signed_char: %hhd, %hhd\n", CHAR_MIN, CHAR_MAX);
  printf("signed_char: %hhb, %hhb\n", CHAR_MIN, CHAR_MAX);
  printf("unsigned_char: %hhu, %hhu\n", 0, UCHAR_MAX);
  printf("unsigned_char: %hhb, %hhb\n", 0, UCHAR_MAX);
  printf("signed short: %hd, %hd\n", SHRT_MIN, SHRT_MAX);
  printf("signed short: %hb, %hb\n", SHRT_MIN, SHRT_MAX);
  printf("unsigned short: %hu, %hu\n", 0, USHRT_MAX);
  printf("unsigned short: %hb, %hb\n", 0, USHRT_MAX);
  printf("signed int: %d, %d\n", INT_MIN, INT_MAX);
  printf("signed int: %b, %b\n", INT_MIN, INT_MAX);
  printf("unsigned int: %u, %u\n", 0, UINT_MAX);
  printf("unsigned int: %b, %b\n", 0, UINT_MAX);
  printf("signed long: %ld, %ld\n", LONG_MIN, LONG_MAX);
  printf("signed long: %lx, %lx\n", LONG_MIN, LONG_MAX);
  printf("unsigned long: %lu, %lu\n", 0lu, ULONG_MAX);
  printf("unsigned long: %lx, %lx\n", 0lu, ULONG_MAX);
}

void calculate() {
  signed char sc_min, sc_max;
  unsigned char uc_min, uc_max;
  signed short ss_min, ss_max;
  unsigned short us_min, us_max;
  signed int si_min, si_max;
  unsigned int ui_min, ui_max;
  signed long sl_min, sl_max;
  unsigned long ul_min, ul_max;

  sc_min = (char) ((unsigned char) ~0 - ((unsigned char) ~0 >> 1));
  sc_max = (char) ((unsigned char) ~0 >> 1);
  printf("signed_char: %hhd, %hhd\n", sc_min, sc_max);
  printf("signed_char: %hhb, %hhb\n", sc_min, sc_max);

  uc_min = 0;
  uc_max = (unsigned char) ~0;
  printf("unsigned char: %hhu, %hhu\n", uc_min, uc_max);
  printf("unsigned char: %hhb, %hhb\n", uc_min, uc_max);

  ss_min = (short) ((unsigned short) ~0 - ((unsigned short) ~0 >> 1));
  ss_max = (short) ((unsigned short) ~0 >> 1);
  printf("signed short: %hd, %hd\n", ss_min, ss_max);
  printf("signed short: %hb, %hb\n", ss_min, ss_max);

  us_min = 0;
  us_max = (unsigned short) ~0;
  printf("unsigned short: %hu, %hu\n", us_min, us_max);
  printf("unsigned short: %hb, %hb\n", us_min, us_max);

  si_min = (int) ((unsigned int) ~0 - ((unsigned int) ~0 >> 1));
  si_max = (int) ((unsigned int) ~0 >> 1);
  printf("signed int: %d, %d\n", si_min, si_max);
  printf("signed int: %b, %b\n", si_min, si_max);

  ui_min = 0;
  ui_max = (unsigned int) ~0;
  printf("unsigned int: %u, %u\n", ui_min, ui_max);
  printf("unsigned int: %b, %b\n", ui_min, ui_max);

  sl_min = (long) ((unsigned long) ~0 - ((unsigned long) ~0 >> 1));
  sl_max = (long) ((unsigned long) ~0 >> 1);
  printf("signed long: %ld, %ld\n", sl_min, sl_max);
  printf("signed long: %lx, %lx\n", sl_min, sl_max);

  ul_min = 0;
  ul_max = (unsigned long) ~0;
  printf("unsigned long: %lu, %lu\n", ul_min, ul_max);
  printf("unsigned long: %lx, %lx\n", ul_min, ul_max);
}

int main() {
  printf("Constants from limits.h\n");
  print_constants();
  printf("\n");
  printf("\"\"\"Calculated\"\"\" limits\n");
  calculate();
  // TODO: print from constants and compute floating-point type ranges
  return 0;
}
