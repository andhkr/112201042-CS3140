%{
#define YYSTYPE int
int mem[26];
%}
%token	NUMBER
%token VAR
%right '='
%left	'+' '-'	  /* left associative, same precedence */
%left	'*' '/'	  /* left assoc., higher precedence */
%%
list:	  /* nothing */
	| list '\n'
	| list expr '\n'    { printf("\t%d\n", $2); }
	;
expr:	  NUMBER    {$$ = $1 ;}
    |     VAR       { $$ = mem[$1]; }
    | VAR '=' expr  {$$ = mem[$1] = $3; }
	| expr '+' expr	{ $$ = $1 + $3; }
	| expr '-' expr	{ $$ = $1 - $3; }
	| expr '*' expr	{ $$ = $1 * $3; }
	| expr '/' expr	{ $$ = $1 / $3; }
	| '(' expr ')'	{ $$ = $2; }
	;
%%
	/* end of grammar */

#include <stdio.h>
#include <ctype.h>
char	*progname;	/* for error messages */
int	lineno = 1;

main(argc, argv)	/* hoc1 */
	char *argv[];
{
	progname = argv[0];
	yyparse();
}

yyerror(s)	/* called for yacc syntax error */
	char *s;
{
	warning(s, (char *) 0);
}

warning(s, t)	/* print warning message */
	char *s, *t;
{
	fprintf(stderr, "%s: %s", progname, s);
	if (t)
		fprintf(stderr, " %s", t);
	fprintf(stderr, " near line %d\n", lineno);
}
