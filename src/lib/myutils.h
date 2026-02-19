#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdbool.h>
#include <stdint.h>

#define BLK "\033[0;30m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"
#define RST "\033[0m"

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

int my_rand(void);
void my_srand(unsigned long seed);

bool is_prime(long a);

void swap(int *a, int *b);
void reverse(char s[]);

// find string `s` in array of strings `in` and return its index or -1 if it's
// not in the array
int find_str(const char s[], char *const in[], const int in_len);

// return pointer to n characters
char *alloc(int n);
// free storage pointed to by p
void afree(char *p);

// write max amnt of `lim` chars from stdin to `s`, return the amnt of chars
// read
int getline(char* s, int lim);
// read input lines
int readlines(char *lineptr[], int maxlines);
// write output lines
void writelines(char *lineptr[], int nlines);

#endif /* MYUTILS_H */
