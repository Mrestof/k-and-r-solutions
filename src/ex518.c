#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1'000

enum { NAME, PARENS, BRACKETS };

int dwc(void);
int wdc(void);

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token [MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int getch(void);
int ungetch(int c);
int prevch = '\0';

int getch(void) {
  if (prevch != '\0') {
    int c = prevch;
    prevch = '\0';
    return c;
  }
  return getchar();
}

int ungetch(int c) {
  if (prevch != '\0') {
    printf("ungetch: too many characters\n");
    return 1;
  }
  prevch = c;
  return 0;
}

/* dcl: parse a declarator */
void dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
  int type;
  if (tokentype == '(') { /* ( dcl ) */
    dcl ();
    if (tokentype != ')')
      printf("error: missing )\n");
  } else if (tokentype == NAME) /* variable name */
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");
  while ((type=gettoken()) == PARENS || type== BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

/* return next token */
int gettoken(void) {
  int c;
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if ( c == '(' ) {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c) ;
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c) ;
    return tokentype = NAME;
  } else
  return tokentype = c;
}

/*convert declaration to words*/
int dwc() {
  while (gettoken() != EOF) { /*1st token on line*/
    strcpy(datatype, token); /*is the datatype */
    out[0] = '\0';
    dcl(); /*parse rest of line*/
    if (tokentype != '\n')
      printf("syntax error\n");
    printf("%s:%s %s\n", name, out, datatype);
  }
  return 0;
}

/* undcl: convert word description to declaration */
int wdc() {
  int type;
  char temp[MAXTOKEN+MAXOUT];
  while (gettoken() != EOF) {
    if (tokentype == '\n')
      continue;
    strcpy(out, token);
    while ((type= gettoken()) != '\n')
      if (type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if (type== '*') {
        sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("invalid input at %s\n", token);
    printf("%s\n", out);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    return 1;
  if (strcmp(argv[1], "dwc") == 0)
    return dwc();
  if (strcmp(argv[1], "wdc") == 0)
    return wdc();
  return 1;
}
