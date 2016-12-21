%option 8bit nodefault


%{
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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"

static int keep;			/* To store start condition */


static char* word(char *s)
{
  char *buf;
  int i, k;
  for (k = 0; isspace(s[k]) || s[k] == '<'; k++) ;
  for (i = k; s[i] && ! isspace(s[i]); i++) ;
  buf = malloc((i - k + 1) * sizeof(char));
  strncpy(buf, &s[k], i - k);
  buf[i - k] = '\0';
  return buf;
}


%}


nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{nl}?"<"
close		">"{nl}?
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
name		{namestart}{namechar}*
data		([^<\n&]|\n[^<&]|\n{esc}|{esc})+
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
version		{open}"?XML VERSION=\"1.0\" ?"{close}
encoding	{open}"?XML-ENCODING"{ws}{name}{ws}?"?"{close}
attdef		{open}"?XML-ATT"

/*
 * The CONTENT mode is used for the content of elements, i.e.,
 * between the ">" and "<" of element tags.
 * The INITIAL mode is used outside the top level element
 * and inside markup.
 */

%s CONTENT


%%

<INITIAL>{ws}		{/* skip */}
<INITIAL>{version}	{return VERSION;}
<INITIAL>{encoding}	{yylval.s = word(yytext + 14); return ENCODING;}
<INITIAL>"/"		{return SLASH;}
<INITIAL>"="		{return EQ;}
<INITIAL>{close}	{BEGIN(CONTENT); return CLOSE;}
<INITIAL>{name}		{yylval.s = strdup(yytext); return NAME;}
<INITIAL>{string}	{yylval.s = strdup(yytext); return VALUE;}
<INITIAL>"?"{close}	{BEGIN(keep); return ENDDEF;}

{attdef}		{keep = YY_START; BEGIN(INITIAL); return ATTDEF;}
{open}{ws}?{name}	{BEGIN(INITIAL); yylval.s= word(yytext); return START;}
{open}{ws}?"/"		{BEGIN(INITIAL); return END;}
{comment}		{yylval.s = strdup(yytext); return COMMENT;}

<CONTENT>{data}		{yylval.s = strdup(yytext); return DATA;}

.			{fprintf(stderr, "!ERROR(%c)\n", *yytext);}
{nl}			{/* skip, must be an extra one at EOF */;}

