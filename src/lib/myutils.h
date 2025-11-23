#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdbool.h>

int my_rand(void);
void my_srand(unsigned long seed);

bool is_prime(long a);

void swap(int *a, int *b);
void reverse(char s[]);

#endif /* MYUTILS_H */
