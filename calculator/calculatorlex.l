%{
    #include "y.tab.h"
    extern int lineno;
%}

%%
[ \t] {;}
[0-9]+ {
    sscanf(yytext,"%d",&yylval);
    return NUMBER;
}
[A-Z] {
    yylval = yytext[0]-'A';
    return VAR;
}
\n {
    lineno++; return '\n';
}
. {
    return yytext[0];}

%%