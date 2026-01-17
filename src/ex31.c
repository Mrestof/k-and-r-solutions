#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 10000000
long a[ARRAY_SIZE];

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, long v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high)/2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else /* found match */
      return mid;
  }
  return -1; /* no match */
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearchv2(int x, long v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  mid = (low+high)/2;
  while (low < high - 1) {
    mid = (low+high)/2;
    if (x < v[mid])
      high = mid;
    else
      low = mid;
  }
  if (x == v[low])
    return low; /* match */
  else
    return -1; /* no match */
}


int main() {
  int i;
  clock_t start, end;

  srand(5);
  for (i = 1, a[0] = 0; i < ARRAY_SIZE; ++i) {
    a[i] = a[i-1] + rand();
  }

  printf("start v1\n");
  fflush(stdout);
  start = clock();
  for (i = 0; i < 10000000; ++i)
    //printf("%d: %d\n", i, binsearchv2(i, a, ARRAY_SIZE));
    binsearch(i, a, ARRAY_SIZE);
  end = clock();
  printf("end v1\n");
  printf("%f\n", (double)(end - start)/CLOCKS_PER_SEC);
  fflush(stdout);

  printf("start v2\n");
  fflush(stdout);
  start = clock();
  for (i = 0; i < 10000000; ++i)
    //printf("%d: %d\n", i, binsearchv2(i, a, ARRAY_SIZE));
    binsearchv2(i, a, ARRAY_SIZE);
  end = clock();
  printf("end v2\n");
  printf("%f\n", (double)(end - start)/CLOCKS_PER_SEC);

  return 0;
}
