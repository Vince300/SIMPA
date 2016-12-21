/*
 * WARNING: This is not an XML 1.0 parser, but an experiment with an XML-like
 * language. See http://www.w3.org/XML/9707/XML-in-C
 *
 * Author: Bert Bos <bert@w3.org>
 * Created: 9 July 1997
 *
 * Copyright © 1997-2000 World Wide Web Consortium
 * See http://www.w3.org/Consortium/Legal/copyright-software-19980720.html
 */

#include <stdio.h>

extern int yyparse(void);

/* yywrap -- return 1 if no more files to parse */
int yywrap(void)
{
  return 1;
}

/* yyerror -- show error message to user */
void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

/* main -- call yyparse and print result */
void main(char *argv, int argc)
{
  int err;

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
}
