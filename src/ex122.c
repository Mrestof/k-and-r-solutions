#include <stdio.h>

#define LIBBSD_OPENBSD_VIS
#include <bsd/vis.h>

#define TEXTWIDTH 80
#define MAXLINE 2048

//#define DEBUG

int readline(char line[], int maxline);
void foldline(char in[], char out[], bool out_mask[], int out_len, int width);

int main() {
  int wid;
  char line[MAXLINE], folded_line[MAXLINE*2];
#ifdef DEBUG
  char output[MAXLINE*2];
#endif
  bool mask[MAXLINE*2];

  while ((wid = readline(line, MAXLINE)) > 0) {
    if (wid >= TEXTWIDTH) {
      foldline(line, folded_line, mask, MAXLINE*2, TEXTWIDTH);
#ifdef DEBUG
      strvis(output, folded_line, VIS_TAB | VIS_NL | VIS_CSTYLE);
      printf("%d: <%s>\n", wid, output);
#else
      printf("%s", folded_line);
#endif
    } else {
#ifdef DEBUG
      strvis(output, line, VIS_TAB | VIS_NL | VIS_CSTYLE);
      printf("%d: <%s>\n", wid, output);
#else
      printf("%s", line);
#endif
    }
  }

  return 0;
}

int readline(char s[], int lim) {
  int c, i;

  for (i=0; (c=getchar())!=EOF && c!='\n'; ++i)
    if (i < lim-1)
      s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

void foldline(char in[], char out[], bool out_mask[], int out_len, int width) {
  int i;
  int cur_pos, blank_pos, offset;
  char cur_char;

  for (i = 0; i < out_len; ++i)
    out_mask[i] = false;

  blank_pos = -1;
  for (i = cur_pos = 0; (cur_char = in[i]) != '\0'; ++i, ++cur_pos) {
    if (cur_pos >= width) {
      if (blank_pos != -1) {
        out_mask[blank_pos] = true;
        cur_pos = 0;
        blank_pos = -1;
      } else if (cur_char == ' ' || cur_char == '\t') {
        out_mask[i] = true;
        cur_pos = 0;
        blank_pos = -1;
      }
    } else if (cur_char == ' ' || cur_char == '\t') {
      blank_pos = i;
    }
  }

  for (i = offset = 0; (cur_char = in[i]) != '\0'; ++i) {
    if (out_mask[i]) {
      out[i+offset] = '\n';
      ++offset;
    }
    out[i+offset] = cur_char;
  }

  out[i+offset] = '\0';
}
