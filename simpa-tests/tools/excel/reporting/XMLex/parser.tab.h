#ifndef BISON_PARSER_TAB_H
# define BISON_PARSER_TAB_H

#ifndef YYSTYPE
typedef union {char *s;} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	VERSION	257
# define	ATTDEF	258
# define	ENDDEF	259
# define	EQ	260
# define	SLASH	261
# define	CLOSE	262
# define	END	263
# define	ENCODING	264
# define	NAME	265
# define	VALUE	266
# define	DATA	267
# define	COMMENT	268
# define	START	269


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_TAB_H */
