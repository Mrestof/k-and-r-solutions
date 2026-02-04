#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000   /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void kr_qsort(
  void *lineptr[], int left, int right, int reverse, int icase, int dirord,
  int (*comp)(void*,void*,int,int)
);
int numcmp(const char *, const char *, int _ic, int _do);
int strcmp_kr(const char *, const char *, int icase, int dirord); /* case insensitive strcmp */

/* sort input lines */
int main(int argc, char *argv[])
{
  int nlines;    /* number of input lines read */
  int numeric = 0;   /* 1 if numeric sort */
  int reverse = 1;   /* -1 if reverse sort */
  int ignore_case = 0; /* 1 if ignore case */
  int directory_order = 0; /* 1 if directory order */

  while (--argc > 0 && **++argv == '-')
    while (*++*argv)
      switch (**argv) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        reverse = -1;
        break;
      case 'f':
        ignore_case = 1;
        break;
      case 'd':
        directory_order = 1;
        break;
      default:
        return 2;
      }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    int (*funcmp)(void*,void*,int,int);
    if (numeric)
      funcmp = (int (*)(void*,void*,int,int))numcmp;
    else
      funcmp = (int (*)(void*,void*,int,int))strcmp_kr;
    kr_qsort(
      (void**) lineptr, 0, nlines-1,
      reverse, ignore_case, directory_order,
      funcmp
    );
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* kr_qsort: sort v[left]...v[right] into increasing order */
void kr_qsort(
  void *v[], int left, int right, int reverse, int icase, int dirord,
  int (*comp)(void*,void*,int,int)
) {
  int i, last;
  void arr_swap(void *v[], int, int);

  if (left >= right)  /* do nothing if array contains */
    return;       /* fewer than two elements */
  arr_swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (reverse * (*comp)(v[i], v[left], icase, dirord) < 0)
      arr_swap(v, ++last, i);
  arr_swap(v, left, last);
  kr_qsort(v, left, last-1, reverse, icase, dirord, comp);
  kr_qsort(v, last+1, right, reverse, icase, dirord, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2, int _ic, int _do)
{
  (void)_ic, (void)_do;
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

int strcmp_kr(const char *s1, const char *s2, int icase, int dirord) {
  char c1, c2;
  int i = 0, j = 0;
  while (s1[i] && s2[j]) {
    if (dirord) {
      if (!(isalnum(s1[i]) || isblank(s1[i]))) {
        i++;
        continue;
      }
      if (!(isalnum(s2[j]) || isblank(s2[j]))) {
        j++;
        continue;
      }
    }
    if (icase) {
      c1 = tolower(s1[i]);
      c2 = tolower(s2[j]);
    } else {
      c1 = s1[i];
      c2 = s2[j];
    }
    if (c1 != c2)
      return c1 - c2;
    i++, j++;
  }
  return 0;
}

void arr_swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
