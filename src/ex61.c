// SKIP: I just don't find this interesting enough
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (int)(sizeof keytab / sizeof keytab[0])

struct key {
  char *word;
  int count;
} keytab[] = {
  {"auto", 0}, {"break", 0}, {"case", 0}, {"char", 0},
  {"const", 0}, {"continue", 0}, {"default", 0}, {"do", 0},
  {"double", 0}, {"else", 0}, {"enum", 0}, {"extern", 0},
  {"float", 0}, {"for", 0}, {"goto", 0}, {"if", 0},
  {"int", 0}, {"long", 0}, {"register", 0}, {"return", 0},
  {"short", 0}, {"signed", 0}, {"sizeof", 0}, {"static", 0},
  {"struct", 0}, {"switch", 0}, {"typedef", 0}, {"union", 0},
  {"unsigned", 0}, {"void", 0}, {"volatile", 0}, {"while", 0},
};

int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);
int getch(void);
void ungetch(int c);

int buf[BUFSIZE];
int bufp = 0;

int main(void)
{
  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;

  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%3d %s\n", keytab[n].count, keytab[n].word);

  return 0;
}

int binsearch(char *word, struct key tab[], int n) {
  int cmp;
  int l, r, m;

  l = 0;
  r = n - 1;

  while (l <= r) {
    m = (r + l) / 2;
    cmp = strcmp(word, tab[m].word);
    if (cmp == 0)
      return m;
    else if (cmp > 0)
      l = m + 1;
    else if (cmp < 0)
      r = m - 1;
  }

  return -1;
}

int getword(char *word, int lim)
{
  int c;
  char *w = word;

  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }

  for (; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }

  *w = '\0';
  return word[0];
}

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
