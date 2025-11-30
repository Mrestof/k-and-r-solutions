#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdbool.h>

int my_rand(void);
void my_srand(unsigned long seed);

bool is_prime(long a);

void swap(int *a, int *b);
void reverse(char s[]);

// find string `s` in array of strings `in` and return its index or -1 if it's
// not in the array
int find_str(const char s[], char *const in[], const int in_len);

#endif /* MYUTILS_H */
